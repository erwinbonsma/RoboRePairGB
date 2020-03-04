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

bool GridScreenTile::canPlaceTile(const GridTile* tile) const {
  if (getTile() != emptyTile) {
    // There's already a tile at this position
    return false;
  }

  if ((tile->mask() & _mask) != 0) {
    // The tile does not fit
    return false;
  }

  // At least one gate of the tile should connect to a gate at a neighbouring tile.
  // - AND with 0xaa to only preserve bits representing gates
  // - Shifting mask one bit to align bits for neighbouring gates with those in tile mask
  return ((tile->mask() & 0xaa) & (_mask << 1)) != 0;
}

bool GridScreenTile::hasOpenEnds() const {
  int tileMask = getTile()->mask() & 0xaa;

  // All gates of the tile should connect to corresponding gates at neighbouring tiles
  return (tileMask & (_mask << 1)) != tileMask;
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
    GridScreenTile& tile = _tiles[i];
    tile.init(ScreenPos(74, 58));
    tile.setTargetPosition(targetScreenPosOf(pos));
    tile.setTile(emptyTile);
    tile.clearMask();
  }
  _lastChangedPos = ScreenPos(74, 58);

  // Set masks for border tiles
  for (int x = _width; --x >= 0; ) {
    GridScreenTile& topTile = _tiles[posToIndex(GridPos(x, 0))];
    topTile.updateMask(Direction::North, NeighbourStatus::NoGate);

    GridScreenTile& bottomTile = _tiles[posToIndex(GridPos(x, _height - 1))];
    bottomTile.updateMask(Direction::South, NeighbourStatus::NoGate);
  }
  for (int y = _height; --y >= 0; ) {
    GridScreenTile& leftTile = _tiles[posToIndex(GridPos(0, y))];
    leftTile.updateMask(Direction::West, NeighbourStatus::NoGate);

    GridScreenTile& rightTile = _tiles[posToIndex(GridPos(_width - 1, y))];
    rightTile.updateMask(Direction::East, NeighbourStatus::NoGate);
  }
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
      _tiles[index].clearMask();
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

  // Update masks (currently not needed, as masks are not used after expansion, but no harm)
  if (_height > oldh) {
    for (int x = oldw; --x >= 0; ) {
      GridIndex index = posToIndex(GridPos(x, oldh));
      GridScreenTile& tile = _tiles[index];
      tile.updateMask(
        Direction::North,
        _tiles[index - _width].getTile() != nullptr ? NeighbourStatus::NoGate : NeighbourStatus::NoTile
      );
    }
  }
  if (_width > oldw) {
    for (int y = oldh; --y >= 0; ) {
      GridIndex index = posToIndex(GridPos(oldw, y));
      GridScreenTile& tile = _tiles[index];
      tile.updateMask(
        Direction::West,
        _tiles[index - 1].getTile() != nullptr ? NeighbourStatus::NoGate : NeighbourStatus::NoTile
      );
    }
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

void TileGrid::updateNeighbourMasks(GridPos pos, const GridTile* tile) {
  for (int d = 4; --d >= 0; ) {
    const Vector2D dirv = dirVectors[d];
    GridPos nbPos(pos.x + dirv.x, pos.y + dirv.y);
    if (contains(nbPos)) {
      GridScreenTile& nbTile = _tiles[posToIndex(nbPos)];
      nbTile.updateMask(
        opposite((Direction)d),
        (tile == emptyTile) ? NeighbourStatus::NoTile : (
          tile->hasGate((Direction)d) 
          ? NeighbourStatus::Gate : NeighbourStatus::NoGate
        )
      );
    }
  }
}

void TileGrid::placeTileAt(GridPos pos, const GridTile* tile, bool force) {
  assertTrue(force || canPlaceTileAt(pos, tile));

  _tiles[posToIndex(pos)].setTile(tile);
  updateNeighbourMasks(pos,  tile);
}

void TileGrid::placeTileAt(GridPos pos, const GridTile* tile, ScreenPos fromPos) {
  assertTrue(canPlaceTileAt(pos, tile));

  GridScreenTile* screenTile = &_tiles[posToIndex(pos)];
  screenTile->setTile(tile);
  updateNeighbourMasks(pos,  tile);

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
      nbTile->hasGate(opposite((Direction)d))
    ) {
      mask |= 0x01 << d;
    }
  }

  const GridTile* tile = tiles + mask;
  placeTileAt(pos, tile, true);
  return tile;
}

bool TileGrid::isComplete() {
  GridScreenTile* p = _tiles;
  while (p < _tilesEnd) {
    if ((p++)->hasOpenEnds()) {
      return false;
    }
  }

  return true;
}

bool TileGrid::canPlaceTileAt(GridPos pos, const GridTile* tile) {
  assertTrue(tile != nullptr);

  return _tiles[posToIndex(pos)].canPlaceTile(tile);
}

bool TileGrid::isPlaceable(const GridTile* tile) {
  GridScreenTile* p = _tiles;
  while (p < _tilesEnd) {
    if ((p++)->canPlaceTile(tile)) {
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
      while (_ready[--j] != index) {
        assertTrue(j >= 0);
      }
      _ready[j] = _ready[--_numReady];
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

  return false;
}

GridMorpher gridMorpher;
