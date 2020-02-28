/*
 * Bumble Bots Re-Pair, a Gamebuino game
 *
 * Copyright 2020, Erwin Bonsma
 */

#include "GridTile.h"

// Size of tiles (in game mode)
constexpr int tileSize = 13;

constexpr int maxWidth = 12;
constexpr int maxHeight = 8;

class Bot;
class TileGrid;
class GridSpec;

class ScreenTile {
  const GridTile* _tile;
  ScreenPos _targetPos;

protected:
  ScreenPos _pos;

public:

  ScreenTile() = default;
  ScreenTile(const ScreenTile& source)
  : _tile(source._tile), _targetPos(source._targetPos), _pos(source._pos) {}

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
  GridScreenTile() = default;
  GridScreenTile(const GridScreenTile& source)
  : ScreenTile(source), _bot(source._bot) {}

  const Bot* getBot() { return _bot; }
  void setBot(const Bot* bot) { _bot = bot; }

  void setPosition(ScreenPos pos) { _pos = pos; }
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

  ScreenPos _lastChangedPos;

  void initOrigin();

public:
  void init(int width, int height);
  void init(const GridSpec& gridSpec);

  int width() const { return _width; }
  int height() const { return _height; }
  GridIndex maxIndex() const { return _maxIndex; }

  void expand(int width, int height);

  GridPos indexToPos(GridIndex index) const {
    return GridPos { .x = (int8_t)(index % _width), .y = (int8_t)(index / _width) };
  }
  GridIndex posToIndex(GridPos pos) const {
    return pos.x + pos.y * _width;
  }

  // Current position, is changes while level is "exploding" into view
  const ScreenPos screenPosOf(GridPos pos);

  // Final position
  const ScreenPos targetScreenPosOf(GridPos pos);

  bool contains(GridPos pos) {
    return pos.x >= 0 && pos.x < _width && pos.y >= 0 && pos.y < _height;
  }

  const GridTile* tileAt(GridPos pos);
  void placeTileAt(GridPos pos, const GridTile* tile, bool force);
  void placeTileAt(GridPos pos, const GridTile* tile, ScreenPos fromPos);

  bool canPlaceTileAt(GridPos pos, const GridTile* tile);
  bool isPlaceable(const GridTile* tile);

  const Bot* claimTile(GridPos pos, const Bot* bot);
  void releaseTile(GridPos pos, const Bot* bot);

  void update();
  void draw();
};

extern TileGrid grid;

