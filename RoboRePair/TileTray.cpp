/*
 * Bumble Bots Re-Pair, a Gamebuino game
 *
 * Copyright 2020, Erwin Bonsma
 */

#include "TileTray.h"

#include "Game.h"

const int tileTraySep = 2;
const int tileTrayMul = tileSize + tileTraySep;

// Global
TileTray tileTray;

TileTray::TileTray() {
  for (int i = maxTraySize; --i >= 0; ) {
    _tiles[i] = &_tileStorage[i];
  }
}

void TileTray::init(int size) {
  assertTrue(size <= maxTraySize);
  _size = size;

  int w = (_size * tileTrayMul - tileTraySep);
  _y0 = 1;
  _x0 = 79 - w / 2;

  for (int i = _size; --i >=0; ) {
    // Reset positions
    _tiles[i]->init(ScreenPos(79 - tileSize / 2, _y0));

    // Set target Y position here, once. It will not change anymore
    _tiles[i]->getTargetPosition()->setY(_y0);
  }

  _cursorPos = ScreenPos(_x0, _y0);

  // Add initial tiles
  _numTiles = 0;
  replenish();
}

void TileTray::updateTargetPositions() {
  for (int i = _numTiles; --i >= 0; ) {
    _tiles[i]->getTargetPosition()->setX(_x0 + i * tileTrayMul);
  }
}

bool TileTray::hasTile(const GridTile* tile) {
  for (int i = _numTiles; --i >= 0; ) {
    if (_tiles[i]->getTile() == tile) {
      return true;
    }
  }

  return false;
}

const GridTile* TileTray::selectNewTile() {
  // Use bit mask to track the tiles that are available as this check is quite expensive.
  uint32_t mask = 0;
  int sum = 0;
  const GridTile* endTileP = tiles + numTiles;
  const GridTile* tileP = endTileP;

  // Note: excluding first (empty) tile on purpose
  while (--tileP > tiles) {
    if (
      tileP->probability() > 0 &&
      !hasTile(tileP) &&
      grid.isPlaceable(tileP)
    ) {
      mask |= 0x1;
      sum += tileP->probability();
    }
    mask <<= 1;
  }

 if (sum == 0) {
    // There's no tile that can be placed which is not on the tray already.
    return nullptr;
  }

  int rndVal = rand() % sum;
  tileP = tiles;
  while (++tileP <= endTileP) {
    mask >>= 1;
    if (mask & 0x1) {
      rndVal -= tileP->probability();
      if (rndVal < 0) {
        return tileP;
      }
    }
  }

  assertTrue(false);
  return nullptr;
}

const GridTile* TileTray::popSelectedTile() {
  assertTrue(_numTiles > 0);

  ScreenTile* poppedTile = _tiles[0];

  // Shift other tiles forwards
  _numTiles--;
  for (int i = 0; i < _numTiles; i++) {
    _tiles[i] = _tiles[i + 1];
  }
  _tiles[_numTiles] = poppedTile;

  updateTargetPositions();

  return poppedTile->getTile();
}

void TileTray::pushTile(const GridTile* tile) {
  assertTrue(_numTiles < _size);

  // Shift other tiles backwards
  ScreenTile* oldLast = _tiles[_numTiles];
  for (int i = _numTiles; --i >= 0; ) {
    _tiles[i + 1] = _tiles[i];
  }
  _tiles[0] = oldLast;
  _tiles[0]->setTile(tile);
  _numTiles++;

  updateTargetPositions();
}

bool TileTray::replenish() {
  assertTrue(_numTiles < _size);

  int iniNumTiles = _numTiles;
  while (_numTiles < _size) {
    const GridTile* newTile = selectNewTile();
    if (newTile == nullptr) {
      // No new tile can be placed
      return _numTiles != iniNumTiles;
    }

    pushTile(newTile);
  }

  return true;
}

bool TileTray::isDone() {
  for (int i = 0; i < _numTiles; i++) {
    if (grid.isPlaceable(_tiles[i]->getTile())) {
      return false;
    }
  }

  return true;
}

void TileTray::switchTiles() {
  assertTrue(_numTiles >= 2);

  ScreenTile* oldFirst = _tiles[0];
  for (int i = 0; i < _numTiles - 1; i++) {
    _tiles[i] = _tiles[i + 1];
  }
  _tiles[_numTiles - 1] = oldFirst;

  updateTargetPositions();
}

void TileTray::placeSelectedTileAt(const GridPos pos) {
  ScreenPos fromPos = _tiles[0]->getPosition();
  grid.placeTileAt(pos, popSelectedTile(), fromPos);
  // TODO: Placement SFX

  if (!replenish() && isDone()) {
    handleGridComplete();
  }
}

void TileTray::update() {
  for (int i = _numTiles; --i >= 0; ) {
    _tiles[i]->update();
  }
}

void TileTray::draw() {
  for (int i = 0; i < _numTiles; i++) {
    _tiles[i]->draw();
  }

  gb.display.setColor(INDEX_GRAY);
  gb.display.drawRect(_cursorPos.getX(), _cursorPos.getY(), 13, 13);

  //gb.display.setCursor(100, 1);
  //for (int i = 0; i < _numTiles; i++) {
  //  gb.display.printf("%d ", _tiles[i]->getTile()->index());
  //}
}

