/*
 * Bumble Bots Re-Pair, a Gamebuino game
 *
 * Copyright 2020, Erwin Bonsma
 */

#include "GridTile.h"

// Size of tiles (in game mode)
constexpr int tileSize = 13;

constexpr int maxWidth = 12;
constexpr int maxHeight = 11; // Applies only for title grid

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
#ifdef SHOW_CLAIMED
  virtual void draw();
#else
  void draw();
#endif
};

// Values chosen for use in GridSceenTile::mask()
enum class NeighbourStatus : uint8_t {
  NoTile = 0,
  Gate = 1,   // Tile with gate to facing tile
  NoGate = 2  // Tile without a gate facing tile
};

class GridScreenTile : public ScreenTile {
  friend class TileGrid;

  const Bot* _bot;

  // Mask representing the tiles and facing gates present at neighbouring tiles.
  uint8_t _mask;

  void clearMask() { _mask = 0; }
  void updateMask(Direction d, NeighbourStatus s) {
    _mask &= ~(0x3 << ((int)d * 2)); // Reset bits for direction
    _mask |= (int)s << ((int)d * 2); // Set bits for direction
  }

  bool canPlaceTile(const GridTile* tile) const;
  bool hasOpenEnds() const;

public:
  GridScreenTile() = default;
  GridScreenTile(const GridScreenTile& source)
  : ScreenTile(source), _bot(source._bot) {}

  const Bot* getBot() { return _bot; }
  void setBot(const Bot* bot) { _bot = bot; }

  void setPosition(ScreenPos pos) { _pos = pos; }

#ifdef SHOW_CLAIMED
  void draw();
#endif
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
  void updateNeighbourMasks(GridPos pos, const GridTile* tile);

public:
  void init(int width, int height, int tileSize = 13);
  void init(const GridSpec& gridSpec, int tileSize = 13);

  int tileSize() const { return _tileSize; }
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
  const GridTile* tileAt(GridIndex index) { return _tiles[index].getTile(); }
  void placeTileAt(GridPos pos, const GridTile* tile, bool force);
  void placeTileAt(GridPos pos, const GridTile* tile, ScreenPos fromPos);
  const GridTile* patchTileAt(GridPos index);

  bool hasOpenEnds(GridPos pos);
  bool isComplete();

  bool canPlaceTileAt(GridPos pos, const GridTile* tile);
  bool isPlaceable(const GridTile* tile);

  bool hasNeighbour(GridPos pos);

  const Bot* claimTile(GridPos pos, const Bot* bot);
  void releaseTile(GridPos pos, const Bot* bot);

  void update();
  void draw();
};

extern TileGrid grid;

enum class MorphStatus : uint8_t {
  Blocked,
  Ready,
  Done
};

class GridMorpher {
  const GridSpec* _targetSpec;
  MorphStatus _status[maxWidth * maxHeight];
  uint8_t _numReady;
  GridIndex _ready[maxWidth * maxHeight];

  void updateTileAt(GridPos pos);
  const GridTile* targetTileAt(GridIndex index);
public:
  void init(const GridSpec* targetSpec);

  bool morphStep();
};

extern GridMorpher gridMorpher;

