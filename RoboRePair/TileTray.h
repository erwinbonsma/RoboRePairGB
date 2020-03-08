/*
 * Bumble Bots Re-Pair, a Gamebuino game
 *
 * Copyright 2020, Erwin Bonsma
 */

#include "TileGrid.h"

const int maxTraySize = 5;

class TileTray {
  uint8_t _size;
  uint8_t _numTiles;

  ScreenPos _cursorPos;
  ScreenTile _tileStorage[maxTraySize];
  ScreenTile* _tiles[maxTraySize];

  uint8_t _x0, _y0;

  void updateTargetPositions();

  bool hasTile(const GridTile* tile);
  const GridTile* selectNewTile();

  const GridTile* popSelectedTile();
  void pushTile(const GridTile* tile);

  bool replenish();

  bool isDone();

public:
  const GridTile* selectedTile() const {
    return _numTiles > 0 ? _tiles[0]->getTile() : nullptr;
  }
  int numAvailableTiles() const { return _numTiles; }

  TileTray();

  void init(int size);

  void switchTiles();
  void placeSelectedTileAt(const GridPos pos);

  void update();
  void draw();
};

extern TileTray tileTray;
