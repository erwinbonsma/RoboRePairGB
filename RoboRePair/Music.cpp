/*
 * Bumble Bots Re-Pair, a Gamebuino game
 *
 * Copyright 2020, Erwin Bonsma
 */

#include "Music.h"

#include "Song.h"

Music music;

void Music::toggleEnabled() {
  if (_enabled) {
    _enabled = false;
    gb.sound.stopSong();
  } else {
    _enabled = true;
    start();
  }
}

void Music::start() {
  if (_enabled) {
    gb.sound.playSong(bumbleBotsSong, true);
  }
}

void Music::stop() {
  if (_enabled) {
    gb.sound.stopSong();
  }
}

void Music::ensureStarted() {
  if (_enabled && !gb.sound.isSongPlaying()) {
    start();
  }
}
