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

