/*
 * Bumble Bots Re-Pair, a Gamebuino game
 *
 * Copyright 2020, Erwin Bonsma
 */

#include <Gamebuino-Meta.h>

#include "Utils.h"

class GridTile;

class Bot {
  GridPos _pos, _nextPos, _prevPos;
  Direction _dir, _nextDir;
  uint8_t _period = 10;
  uint8_t _clk;

  void handleMove(const GridTile& tile);
  void moveStep();

public:
  void update();
  void draw();

  void init(GridPos pos, Direction dir);
};

