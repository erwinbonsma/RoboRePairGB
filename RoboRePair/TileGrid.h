/*
 * Bumble Bots Re-Pair, a Gamebuino game
 *
 * Copyright 2020, Erwin Bonsma
 */

#include <Gamebuino-Meta.h>

#include "GridTile.h"
#include "Utils.h"

const int maxWidth = 12;
const int maxHeight = 8;

class TileGrid;

class ScreenTile {
  friend TileGrid;

  const GridTile* _tile;
  ScreenPos _pos;
  ScreenPos _targetPos;

public:
  ScreenTile();

  void update();
  void draw();
};

using GridIndex = int;

class GridPos {
  uint8_t _x;
  uint8_t _y;

public:
  int getX() { return _x; }
  int getY() { return _y; }

  GridPos(int x, int y) : _x(x), _y(y) {}
};

class TileGrid {
  uint8_t _tileSize;

  uint8_t _width;
  uint8_t _height;
  GridIndex _maxIndex; // exclusive

  uint8_t _x0;
  uint8_t _y0;

  ScreenTile _tiles[maxWidth * maxHeight];

  ScreenPos screenPosFor(GridPos);

public:
  void init(uint8_t width, uint8_t height);

  GridIndex maxIndex() { return _maxIndex; }
  GridPos indexToPos(GridIndex index) { return GridPos(index % _width, index / _width); }
  GridIndex posToIndex(GridPos pos) { return pos.getX() + _width * pos.getY();  }

  void placeTileAt(GridPos pos, const GridTile* tile, bool force);

  void update();
  void draw();
};

