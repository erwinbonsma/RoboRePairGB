/*
 * Bumble Bots Re-Pair, a Gamebuino game
 *
 * Copyright 2020, Erwin Bonsma
 */

#include <Gamebuino-Meta.h>

#include "Utils.h"

class GridTile {
  uint8_t _entries;
  uint16_t _connections;
  uint8_t _probability;
  uint8_t _index;

public:
  bool hasEntry(Direction entry) const {
    return _entries & (0x1 << (int)entry);
  }

  bool pathExists(Direction from, Direction to) const {
    return _connections & ((0x1 << (int)from) << (int)to * 4);
  }

  Direction randomExitFrom(Direction entry) const;

  int probability() const { return _probability; }

  int index() const { return _index; }

  GridTile(uint8_t entries, uint16_t connections, uint8_t probability);
};

const int numTiles = 16;
extern const GridTile tiles[numTiles];

