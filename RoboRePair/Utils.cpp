/*
 * Bumble Bots Re-Pair, a Gamebuino game
 *
 * Copyright 2020, Erwin Bonsma
 */

#include "Utils.h"

ScreenPos::ScreenPos(int x, int y) {
  _x = (int16_t)(x << 4);
  _y = (int16_t)(y << 4);
}

void ScreenPos::lerp(ScreenPos target, uint16_t amount) {
  assertTrue(amount <= 256);
  _x = (_x * (256 - amount) + target._x * amount) >> 8;
  _y = (_y * (256 - amount) + target._y * amount) >> 8;
}

void assertFailed(const char *function, const char *file, int lineNo, const char *expression) {
  if (SerialUSB) {
    SerialUSB.println("=== ASSERT FAILED ===");
    SerialUSB.println(function);
    SerialUSB.println(file);
    SerialUSB.println(lineNo, DEC);
    SerialUSB.println(expression);
    SerialUSB.flush();
  }

  while (1) {
    if (gb.update()) {
      gb.display.clear();
      gb.display.setColor(RED);
      gb.display.println("Assert failed:");
      gb.display.println(function);
      gb.display.println(file);
      gb.display.println(lineNo, DEC);
      gb.display.println(expression);
    }
  }
}
