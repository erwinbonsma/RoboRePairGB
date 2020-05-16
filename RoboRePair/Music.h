/*
 * Bumble Bots Re-Pair, a Gamebuino game
 *
 * Copyright 2020, Erwin Bonsma
 */

#include <Gamebuino-Meta.h>

class Music {
  bool _enabled = true;

public:
  bool isEnabled() { return _enabled; }

  void toggleEnabled();

  // The below methods have mo effect when music is disabled
  void start();
  void stop();

  // Starts music if it was not playing already
  void ensureStarted();
};

extern Music music;
