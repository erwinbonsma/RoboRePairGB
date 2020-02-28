/*
 * Bumble Bots Re-Pair, a Gamebuino game
 *
 * Copyright 2020, Erwin Bonsma
 */

#include "TileGrid.h"
#include "Images.h"
#include "Levels.h"

TileGrid grid;

const GridTile* emptyTile = &tiles[0];

void ScreenTile::init(ScreenPos pos) {
  _pos = pos;
  _targetPos = pos;
  _tile = nullptr;
}

void ScreenTile::update() {
  _pos.lerp(_targetPos, 64);
}

void ScreenTile::draw() {
  tilesImage.setFrame(_tile->index());
  gb.display.drawImage(_pos.getX(), _pos.getY(), tilesImage);
}

void TileGrid::initOrigin() {
  _x0 = 80 - _width * _tileSize / 2;
  _y0 = 20;
}

void TileGrid::init(int width, int height) {
  _width = width;
  _height = height;
  _maxIndex = width * height;
  _tilesEnd = _tiles + _maxIndex;
  _tileSize = 13;

  initOrigin();

  for (int i = _maxIndex; --i >= 0; ) {
    GridPos pos = indexToPos(i);
    _tiles[i].init(ScreenPos(74, 58));
    _tiles[i].setTargetPosition(targetScreenPosOf(pos));
    _tiles[i].setTile(emptyTile);
  }
  _lastChangedPos = ScreenPos(74, 58);
}

void TileGrid::init(const GridSpec& gridSpec) {
  init(gridSpec.w, gridSpec.h);

  const uint8_t* tileIndices = gridSpec.tiles;
  for (int i = _maxIndex; --i >= 0; ) {
    GridPos pos = indexToPos(i);
    placeTileAt(pos, &tiles[tileIndices[i]], true);
  }
}

void TileGrid::expand(int width, int height) {
  assertTrue(width >= _width && height >= _height);
  assertTrue(width <= maxWidth && height <= maxHeight);

  int oldw = _width;
  int oldh = _height;

  _width = width;
  _height = height;
  _maxIndex = _width * _height;
  _tilesEnd = _tiles + _maxIndex;

  initOrigin();

  // Update tiles
  for (int index = _maxIndex; --index >= 0; ) {
    GridPos pos = indexToPos(index);
    if (pos.x >= oldw || pos.y >= oldh) {
      // Create new, empty tile
      _tiles[index].init(ScreenPos(74, 58));
      _tiles[index].setTile(emptyTile);
    } else {
      GridIndex oldIndex = pos.x + pos.y * oldw;
      if (index != oldIndex) {
        // Copy tile from old position
        _tiles[index] = _tiles[oldIndex];
      }
    }
    // Update target position
    _tiles[index].setTargetPosition(targetScreenPosOf(pos));
  }
}

const ScreenPos TileGrid::targetScreenPosOf(GridPos pos) {
  return ScreenPos(
    _x0 + pos.x * _tileSize,
    _y0 + pos.y * _tileSize
  );
}

const ScreenPos TileGrid::screenPosOf(GridPos pos) {
  return _tiles[posToIndex(pos)].getPosition();
}

const GridTile* TileGrid::tileAt(GridPos pos) {
  if (contains(pos)) {
    const GridTile* tile = _tiles[posToIndex(pos)].getTile();
    if (tile != emptyTile) {
      return tile;
    } else {
      // The empty tile is only used for drawing purposes. Pretend it does not exist.
      return nullptr;
    }
  } else {
    // Return the empty tile to prevent connections of the grid.
    return emptyTile;
  }
}

void TileGrid::placeTileAt(GridPos pos, const GridTile* tile, bool force) {
  assertTrue(force || canPlaceTileAt(pos, tile));

  _tiles[posToIndex(pos)].setTile(tile);
}

void TileGrid::placeTileAt(GridPos pos, const GridTile* tile, ScreenPos fromPos) {
  assertTrue(canPlaceTileAt(pos, tile));

  GridScreenTile* screenTile = &_tiles[posToIndex(pos)];
  screenTile->setTile(tile);
  _lastChangedPos = screenTile->getPosition();
  screenTile->setPosition(fromPos);
}

const GridTile* TileGrid::patchTileAt(GridPos pos) {
  int mask = 0;
  for (int d = 4; --d >= 0; ) {
    const Vector2D dirv = dirVectors[d];
    GridPos nbPos(pos.x + dirv.x, pos.y + dirv.y);
    const GridTile* nbTile = tileAt(nbPos);
    if (
      nbTile != nullptr &&
      nbTile->hasEntry(opposite((Direction)d))
    ) {
      mask |= 0x01 << d;
    }
  }

  const GridTile* tile = tiles + mask;
  placeTileAt(pos, tile, true);
  return tile;
}

bool TileGrid::canPlaceTileAt(GridPos pos, const GridTile* tile) {
  assertTrue(tile != nullptr);

  if (tileAt(pos) != nullptr) {
    // There's already a tile at this position
    return false;
  }

  bool connects = false;
  for (int d = 4; --d >= 0; ) {
    const Vector2D dirv = dirVectors[d];
    const GridTile* nbTile = tileAt(GridPos(pos.x + dirv.x, pos.y + dirv.y));
    bool hasPath = tile->hasEntry((Direction)d);
    if (nbTile != nullptr) {
      if (hasPath != nbTile->hasEntry( opposite((Direction)d) )) {
        return false;
      }
      connects |= hasPath;
    }
  }

  return connects;
}

bool TileGrid::isPlaceable(const GridTile* tile) {
  for (int i = _maxIndex; --i >= 0; ) {
    if (canPlaceTileAt(indexToPos(i), tile)) {
      return true;
    }
  }

  return false;
}

bool TileGrid::hasNeighbour(GridPos pos) {
  for (int d = 4; --d >= 0; ) {
    const Vector2D dirv = dirVectors[d];
    GridPos nbPos(pos.x + dirv.x, pos.y + dirv.y);
    if (contains(nbPos) && tileAt(nbPos) != nullptr) {
      return true;
    }
  }
  return false;
}

Bot const* TileGrid::claimTile(GridPos pos, const Bot* bot) {
  int index = posToIndex(pos);
  const Bot* other = _tiles[index].getBot();
  if (other == nullptr) {
    _tiles[index].setBot(bot);
    return bot;
  } else {
    return other;
  }
}

void TileGrid::releaseTile(GridPos pos, const Bot* bot) {
  int index = posToIndex(pos);
  Bot const* claimer = _tiles[index].getBot();
  if (claimer == bot) {
    _tiles[index].setBot(nullptr);
  }
}

void TileGrid::update() {
  GridScreenTile* p = _tiles;
  while (p < _tilesEnd) {
    (p++)->update();
  }
}

void TileGrid::draw() {
  // Draw this to not show an ugly gap when placing a new tile
  tilesImage.setFrame(0);
  gb.display.drawImage(_lastChangedPos.getX(), _lastChangedPos.getY(), tilesImage);

  GridScreenTile* p = _tiles;
  while (p < _tilesEnd) {
    (p++)->draw();
  }
}

void GridMorpher::dumpReady(const char* when) {
  SerialUSB.printf("%s: ", when);
  for (int i = _numReady; --i >= 0; ) {
    SerialUSB.printf("%d ", _ready[i]);
  }
  SerialUSB.println();
}

const GridTile* GridMorpher::targetTileAt(GridIndex index) {
  return tiles + _targetSpec->tiles[(int)index];
}

void GridMorpher::updateTileAt(GridPos pos) {
  GridIndex index = grid.posToIndex(pos);
  if (_status[index] == MorphStatus::Blocked) {
    _status[index] = MorphStatus::Ready;
    _ready[_numReady++] = index;
  }
  if (_status[index] == MorphStatus::Ready) {
    const GridTile* tile = grid.patchTileAt(pos);
    if (tile == targetTileAt(index)) {
      // No further update needed
      _status[index] = MorphStatus::Done;

      // Find and remove it from the ready queue
      int j = _numReady;
      SerialUSB.printf("Removing %d\n", index);
      while (_ready[--j] != index) {
        assertTrue(j >= 0);
      }
      _ready[j] = _ready[--_numReady];
      dumpReady("#3");
    }
  }
}

void GridMorpher::init(const GridSpec* targetSpec) {
  _targetSpec = targetSpec;
  grid.expand(targetSpec->w, targetSpec->h);

  _numReady = 0;
  for (GridIndex i = grid.maxIndex(); --i >= 0; ) {
    const GridTile* tile = grid.tileAt(i);
    if (tile == targetTileAt(i)) {
      _status[i] = MorphStatus::Done;
    } else if (tile != nullptr || grid.hasNeighbour(grid.indexToPos(i))) {
      _status[i] = MorphStatus::Ready;
      _ready[_numReady++] = i;
    } else {
      _status[i] = MorphStatus::Blocked;
    }
  }
  dumpReady("#0");
}

bool GridMorpher::morphStep() {
  if (_numReady == 0) {
    // We're done!
    return true;
  }

  // Select random ready tile
  int rndVal = rand() % _numReady;
  GridIndex index = _ready[rndVal];
  _ready[rndVal] = _ready[--_numReady];

  SerialUSB.printf("Selected %d at %d\n", index, rndVal);
  dumpReady("#1");

  GridPos pos = grid.indexToPos(index);
  grid.placeTileAt(pos, targetTileAt(index), true);
  _status[index] = MorphStatus::Done;

  // Update neighbours
  for (int d = 4; --d >= 0; ) {
    const Vector2D dirv = dirVectors[d];
    GridPos nbPos(pos.x + dirv.x, pos.y + dirv.y);
    if (grid.contains(nbPos)) {
      updateTileAt(nbPos);
    }
  }
  dumpReady("#2");

  return false;
}

GridMorpher gridMorpher;
