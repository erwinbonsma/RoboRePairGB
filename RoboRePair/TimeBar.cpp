/*
 * Bumble Bots Re-Pair, a Gamebuino game
 *
 * Copyright 2020, Erwin Bonsma
 */

#include "TimeBar.h"

#include "Game.h"
#include "Images.h"
#include "Lights.h"
#include "Utils.h"

// Globals
TimeBar timeBar;

const int numTimebarParts = 4;

struct TimeBarSpec {
  uint8_t len;
  uint8_t unit;
  ColorIndex colorMain;
  ColorIndex colorDark;
};

// Length, Time unit, Main color, Shadow color
const TimeBarSpec timebarSpecs[numTimebarParts] = {
 TimeBarSpec {.len =  4, .unit =  1, .colorMain = INDEX_YELLOW,   .colorDark = INDEX_ORANGE},
 TimeBarSpec {.len =  8, .unit =  2, .colorMain = INDEX_BEIGE,    .colorDark = INDEX_ORANGE},
 TimeBarSpec {.len =  8, .unit =  4, .colorMain = INDEX_ORANGE,   .colorDark = INDEX_BROWN},
 TimeBarSpec {.len = 24, .unit = 16, .colorMain = INDEX_BROWN,    .colorDark = INDEX_BROWN}

};
const TimeBarSpec* blinkLimitSpec = &timebarSpecs[2]; // Inclusive

bool TimeBar::scoreTicks() {
  // Avoid that ticksRemaining becomes zero while scoring.(so that scoring nevers triggers TIMED OUT)
  if (_ticksRemaining > fps) {
    incScore(1);
    _ticksRemaining -= fps;
    return true;
  } else {
    return false;
  }
}

void TimeBar::stop(bool ignoreTimeout) {
  _stopped = true;
  if (ignoreTimeout && _ticksRemaining == 0) {
    // Prevent showing of "Timed out". This is used when the time runs out while all bots are already
    // pairing
    _ticksRemaining = 1;
  }
}

void TimeBar::init(int seconds) {
  _ticksRemaining = seconds * fps;
  _stopped = false;
}

bool TimeBar::update() {
  if (_stopped) {
    return true;
  }

  if (_ticksRemaining > 0) {
    _ticksRemaining--;
  }

  return (_ticksRemaining > 0);
}

const TimeBarSpec* TimeBar::drawTimeBar() {
  const TimeBarSpec* spec = timebarSpecs;
  int secs = _ticksRemaining / fps;
  int x = 159;
  while (secs > 0) {
    int l = min(spec->len, max(1, secs/spec->unit));

    gb.display.setColor(spec->colorMain);
    gb.display.fillRect(x - l, 10, l, 3);
    gb.display.setColor(spec->colorDark);
    gb.display.drawFastHLine(x - l, 13, l);

    secs -= spec->len * spec->unit;
    if (secs <= 0) {
      return spec;
    }
    x -= spec->len;
    ++spec;
  }

  return spec;
}

void TimeBar::flashLights(const TimeBarSpec* spec) {
  if (spec <= blinkLimitSpec) {
    uint8_t i = gb.frameCount % (spec->unit * fps);
    if (i < 12) {
      drawLight(0, 3 - i / 3, spec->colorMain);
      drawLight(1, i / 3, spec->colorMain);
    }
  }
}

void TimeBar::draw() {
  if (_ticksRemaining == 0) {
    gb.display.drawImage(127, 9, timedOutImage);
  }  else {
    const TimeBarSpec* spec = drawTimeBar();
    if (!_stopped) {
      flashLights(spec);
    }
  }
}

