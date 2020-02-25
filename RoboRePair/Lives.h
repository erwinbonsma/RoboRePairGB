/*
 * Bumble Bots Re-Pair, a Gamebuino game
 *
 * Copyright 2020, Erwin Bonsma
 */

#include <Gamebuino-Meta.h>

class Lives {
  uint8_t _numLives;
  uint8_t _drawLives;
  uint8_t _clk;

public:
  bool inc();
  bool dec();

  void init();

  void update();
  void draw();
};

extern Lives lives;
