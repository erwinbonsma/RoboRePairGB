/*
 * Bumble Bots Re-Pair, a Gamebuino game
 *
 * Copyright 2020, Erwin Bonsma
 */

#include "GridTile.h"

static int _nxtIndex = 0;

GridTile::GridTile(uint8_t entries, uint16_t connections, uint8_t probability) {
  _entries = entries;
  _connections = connections;
  _probability = probability;
  _index = _nxtIndex++;
}

Direction GridTile::exitFrom(Direction entry) const {
  int val = (_connections >> ((int)entry * 4)) & 0xF;
  int num = 0;
  int dir = 0;
  Direction firstDir = Direction::None;

  while (val != 0) {
    if (val & 0x1) {
      num++;
      if (num >= 2) {
        return Direction::Multiple;
      } else {
        firstDir = (Direction)dir;
      }
    }
    ++dir;
    val >>= 1;
  }
  assertTrue(num == 1);

  return firstDir;
}

Direction GridTile::randomExitFrom(Direction entry) const {
  int bits = (_connections >> ((int)entry * 4)) & 0xF;

  // Determine number of exits
  int num = 0;
  int val = bits;
  while (val != 0) {
    if (val & 0x1) {
      num++;
    }
    val >>= 1;
  }
  assertTrue(num > 0);

  // Pick one
  int select = rand() % num;
  int dir = 0;
  val = bits;
  while (val != 0) {
    if (val & 0x1) {
      if (select-- == 0) {
        return (Direction)dir;
      }
    }
    val >>= 1;
    dir++;
  }
  assertTrue(false);

  return Direction::North; // Should never get here
}

const GridTile tiles[numTiles] = {
  GridTile( 0, 0x0000, 0),
  GridTile( 1, 0x0001, 1),
  GridTile (2, 0x0020, 1),
  GridTile( 3, 0x0012, 2),
  GridTile( 4, 0x0400, 1),
  GridTile( 5, 0x0104, 4),
  GridTile( 6, 0x0240, 2),
  GridTile( 7, 0x0252, 2),
  GridTile( 8, 0x8000, 1),
  GridTile( 9, 0x1008, 2),
  GridTile(10, 0x2080, 4),
  GridTile(11, 0x101A, 2),
  GridTile(12, 0x4800, 2),
  GridTile(13, 0x5808, 2),
  GridTile(14, 0x4A40, 2),
  GridTile(15, 0x2184, 2)
};

