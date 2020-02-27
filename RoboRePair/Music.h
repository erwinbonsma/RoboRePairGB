/*
 * Bumble Bots Re-Pair, a Gamebuino game
 *
 * Copyright 2020, Erwin Bonsma
 */

#include <Gamebuino-Meta.h>

const char *const introTrack = "bb-track1-intro.wav";
const char *const loopTrack = "bb-track1-loop.wav";

class Music {
  int8_t _track;
  bool _enabled = true;
  bool _stopped = true;

public:
  bool isEnabled() { return _enabled; }
  bool isStopped() { return _stopped; }

  void toggleEnabled();

  // No effect when music is disabled
  void start();
  void stop();

  void update() {
    if (!_stopped && !gb.sound.isPlaying(_track)) {
      _track = gb.sound.play(loopTrack, true);
    }
  }
};

extern Music music;

