/*
 * Bumble Bots Re-Pair, a Gamebuino game
 *
 * Copyright 2020, Erwin Bonsma
 */

#include <Gamebuino-Meta.h>

class TimeBar {
  uint16_t _ticksRemaining;

public:
  bool scoreTicks();

  void init(int seconds);

  bool update();
  void draw();
};

extern TimeBar timeBar;

