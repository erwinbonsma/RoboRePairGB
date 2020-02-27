/*
 * Bumble Bots Re-Pair, a Gamebuino game
 *
 * Copyright 2020, Erwin Bonsma
 */

#include "Music.h"

Music music;

void Music::toggleEnabled() {
  if (_enabled) {
    _enabled = false;
    if (!_stopped) {
      gb.sound.stop(_track);
    }
  } else {
    _enabled = true;
    if (!_stopped) {
      _track = gb.sound.play(introTrack);
    }
  }
}

void Music::start() {
  if (_enabled && _stopped) {
    _stopped = false;
    _track = gb.sound.play(introTrack);
  }
}

void Music::stop() {
  if (_enabled && !_stopped) {
    _stopped = true;
    gb.sound.stop(_track);
  }
}


