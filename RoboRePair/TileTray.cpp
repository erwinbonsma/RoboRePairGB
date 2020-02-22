/*
 * Bumble Bots Re-Pair, a Gamebuino game
 *
 * Copyright 2020, Erwin Bonsma
 */

#include "TileTray.h"

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
  while (_numTiles < _size && replenish()) {}
}

void TileTray::updateTargetPositions() {
  for (int i = _numTiles; --i >= 0; ) {
    _tiles[i]->getTargetPosition()->setX(_x0 + i * tileTrayMul);
  }
}

const GridTile* TileTray::selectNewTile() {
  // TODO
  return &tiles[_numTiles];
}

bool TileTray::replenish() {
  assertTrue(_numTiles < _size);

  const GridTile* newTile = selectNewTile();
  if (newTile == nullptr) {
    // No new tile can be placed
    return false;
  }

  // Shift other tiles backwards
  ScreenTile* oldLast = _tiles[_numTiles];
  for (int i = _numTiles; --i >= 0; ) {
    _tiles[i + 1] = _tiles[i];
  }
  _tiles[0] = oldLast;
  _tiles[0]->setTile(newTile);
  _numTiles++;

  updateTargetPositions();

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

// TODO:  void placeTile();

void TileTray::update() {
  for (int i = _numTiles; --i >= 0; ) {
    _tiles[i]->update();
  }
}

void TileTray::draw() {
  for (int i = 0; i < _numTiles; i++) {
    _tiles[i]->draw();
  }

  gb.display.setColor(WHITE);
  gb.display.drawRect(_cursorPos.getX(), _cursorPos.getY(), 13, 13);
}

