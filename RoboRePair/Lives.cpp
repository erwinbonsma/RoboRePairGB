/*
 * Bumble Bots Re-Pair, a Gamebuino game
 *
 * Copyright 2020, Erwin Bonsma
 */

#include "Lives.h"

#include "Images.h"
#include "Utils.h"

// Global
Lives lives;

bool Lives::inc() {
  if (_numLives >= 3) {
    return false;
  }

  ++_numLives;
  return true;
}

bool Lives::dec() {
  if (_numLives == 0) {
    return false;
  }

  --_numLives;
  return true;
}

void Lives::init() {
  _numLives = 3;
  _drawLives = 0;
  _clk = 0;
}

void Lives::update() {
  ++_clk;
  if (_clk % 4 != 0) {
    return;
  }

  int delta = _numLives * 8 - _drawLives;
  _drawLives += sgn(delta);
}

void Lives::draw() {
  // Draw full/static lives
  livesImage.setFrame(0);
  int fullLives = _drawLives >> 3; // Fast division by eight
  for (int i = fullLives; --i >= 0; ) {
    gb.display.drawImage(152 - 8 * i, 1, livesImage);
  }

  // Draw live that is appearing/disappearing
  int mod = _drawLives & 0x07; // Fast modulus eight
  if (mod != 0) {
    livesImage.setFrame(8 - mod);
    gb.display.drawImage(152 - 8 * fullLives, 1, livesImage);
  }
}

