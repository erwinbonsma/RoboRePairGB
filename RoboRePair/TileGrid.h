/*
 * Bumble Bots Re-Pair, a Gamebuino game
 *
 * Copyright 2020, Erwin Bonsma
 */

#include "GridTile.h"

// Size of tiles (in game mode)
const int tileSize = 13;

const int maxWidth = 12;
const int maxHeight = 8;

class Bot;
class TileGrid;
class GridSpec;

class ScreenTile {
  const GridTile* _tile;
  ScreenPos _pos;
  ScreenPos _targetPos;

public:

  ScreenTile() = default;

  const GridTile* getTile() const { return _tile; }
  void setTile(const GridTile* tile) { _tile = tile; }

  ScreenPos getPosition() const { return _pos; }
  ScreenPos* getTargetPosition() { return &_targetPos; }

  void setTargetPosition(ScreenPos targetPos) { _targetPos = targetPos; }

  void init(ScreenPos pos);

  void update();
  void draw();
};

class GridScreenTile : public ScreenTile {
  const Bot* _bot;

public:
  const Bot* getBot() { return _bot; }
  void setBot(const Bot* bot) { _bot = bot; }
};

using GridIndex = int;

class TileGrid {
  uint8_t _tileSize;

  uint8_t _width;
  uint8_t _height;
  GridIndex _maxIndex; // exclusive

  uint8_t _x0;
  uint8_t _y0;

  GridScreenTile _tiles[maxWidth * maxHeight];
  GridScreenTile* _tilesEnd;

public:
  void init(uint8_t width, uint8_t height);
  void init(const GridSpec& gridSpec);

  int width() const { return _width; }
  int height() const { return _height; }
  GridIndex maxIndex() const { return _maxIndex; }

  GridPos indexToPos(GridIndex index) const {
    return GridPos { .x = (int8_t)(index % _width), .y = (int8_t)(index / _width) };
  }
  GridIndex posToIndex(GridPos pos) const {
    return pos.x + _width * pos.y;
  }

  // Current position, is changes while level is "exploding" into view
  const ScreenPos screenPosOf(GridPos pos);

  // Final position
  const ScreenPos targetScreenPosOf(GridPos pos);

  const GridTile& tileAt(GridPos pos);
  void placeTileAt(GridPos pos, const GridTile* tile, bool force);

  const Bot* claimTile(GridPos pos, const Bot* bot);
  void releaseTile(GridPos pos, const Bot* bot);

  void update();
  void draw();
};

extern TileGrid grid;

