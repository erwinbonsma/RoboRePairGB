/*
 * Bumble Bots Re-Pair, a Gamebuino game
 *
 * Copyright 2020, Erwin Bonsma
 */

#include <Gamebuino-Meta.h>

class TimeBarSpec;

class TimeBar {
  uint16_t _ticksRemaining;
  bool _stopped;

  const TimeBarSpec* drawTimeBar();
  void flashLights(const TimeBarSpec* spec);

public:
  bool scoreTicks();
  void stop(bool ignoreTimeout = false);

  void init(int seconds);

  bool update();
  void draw();
};

extern TimeBar timeBar;

