/*
 * Bumble Bots Re-Pair, a Gamebuino game
 *
 * Copyright 2020, Erwin Bonsma
 */

#include "TimeBar.h"

#include "Game.h"
#include "Images.h"
#include "Utils.h"

// Globals
TimeBar timeBar;

const int numTimebarParts = 4;

// Length, Time unit, Main color, Shadow color
const uint8_t timebarSpecs[numTimebarParts][4] = {
 { 4,  1, (uint8_t)INDEX_YELLOW,   (uint8_t)INDEX_ORANGE},
 { 8,  2, (uint8_t)INDEX_ORANGE,   (uint8_t)INDEX_BROWN},
 {16,  4, (uint8_t)INDEX_BROWN ,   (uint8_t)INDEX_DARKGRAY},
 {28, 16, (uint8_t)INDEX_DARKGRAY, (uint8_t)INDEX_DARKGRAY}
};

bool TimeBar::scoreTicks() {
  if (_ticksRemaining >= fps) {
    incScore(1);
    _ticksRemaining -= fps;
    return true;
  } else {
    return false;
  }
}

void TimeBar::init(int seconds) {
  _ticksRemaining = seconds * fps;
}

bool TimeBar::update() {
  if (_ticksRemaining > 0) {
    _ticksRemaining--;
  }

  return (_ticksRemaining > 0);
}

void TimeBar::draw() {
  if (_ticksRemaining == 0) {
    gb.display.drawImage(127, 9, timedOutImage);
  }  else {
    int i = 0;
    int secs = _ticksRemaining / fps;
    int x = 158;
    while (secs > 0) {
      const uint8_t* spec = timebarSpecs[i];
      int l = min(spec[0], max(1, secs/spec[1]));

      gb.display.setColor((ColorIndex)spec[2]);
      gb.display.fillRect(x - l, 10, l, 3);
      gb.display.setColor((ColorIndex)spec[3]);
      gb.display.drawFastHLine(x - l, 13, l);

      secs -= spec[0] * spec[1];
      x -= spec[0];
      ++i;
    }
  }
}

