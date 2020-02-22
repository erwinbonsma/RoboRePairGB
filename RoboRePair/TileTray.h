/*
 * Bumble Bots Re-Pair, a Gamebuino game
 *
 * Copyright 2020, Erwin Bonsma
 */

#include "TileGrid.h"

const int maxTraySize = 3;

class TileTray {
  uint8_t _size;
  uint8_t _numTiles;

  ScreenPos _cursorPos;
  ScreenTile _tileStorage[maxTraySize];
  ScreenTile* _tiles[maxTraySize];

  uint8_t _x0, _y0;

  void updateTargetPositions();

  const GridTile* selectNewTile();

  bool replenish();
  const GridTile* popSelectedTile();

  bool isDone();

public:
  const GridTile* selectedTile() const {
    return _numTiles > 0 ? _tiles[0]->getTile() : nullptr;
  }
  int numTiles() const { return _numTiles; }

  TileTray();

  void init(int size);

  void switchTiles();
  void placeTile();

  void update();
  void draw();
};

extern TileTray tileTray;
