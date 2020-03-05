/*
 * Bumble Bots Re-Pair, a Gamebuino game
 *
 * Copyright 2020, Erwin Bonsma
 */

#include "Utils.h"

class GridTile {
  uint8_t _gates;
  uint8_t _probability;
  uint8_t _index;
  uint8_t _mask;
  uint16_t _connections;
  bool _hardCorners;

public:
  // Returns true iff the tile has an entry/exit at the given side of the tile.
  bool hasGate(Direction gate) const {
    return _gates & (0x1 << (int)gate);
  }

  // Returns true iff a bot can move from the gate at "from" to the gate at "to".
  bool pathExists(Direction from, Direction to) const {
    return _connections & ((0x1 << (int)from) << (int)to * 4);
  }

  // Returns the only exit gate from the given entry or Direction::Multiple in case there is more than one
  Direction exitFrom(Direction entry) const;

  Direction randomExitFrom(Direction entry) const;

  int probability() const { return _probability; }
  int index() const { return _index; }
  bool hasHardCorners() const { return _hardCorners; }

  // Returns a mask that represents the tile's entries/exits. It can be used to quickly determine if
  // a tile can be placed at a certain grid location given the tiles at its neighbours. See the
  // GridScreenTile class for details.
  int mask() const { return _mask; }

  GridTile(uint8_t entries, uint16_t connections, uint8_t probability, bool hardCorners = false);
};

const int numTiles = 25;
extern const GridTile tiles[numTiles];

