/*
 * Bumble Bots Re-Pair, a Gamebuino game
 *
 * Copyright 2020, Erwin Bonsma
 */

#include "Utils.h"

int orientation(Vector2D v1, Vector2D v2) {
  int val = v1.y * v2.x - v1.x * v2. y;
  return (val == 0) ? 0 : ((val > 0) ? 1 : -1);
}

extern const Vector2D dirVectors[4] = {
  Vector2D { .x = 0, .y = -1 },
  Vector2D { .x = 1, .y = 0 },
  Vector2D { .x = 0, .y = 1 },
  Vector2D { .x = -1, .y = 0 }
};

ScreenPos::ScreenPos(int x, int y) {
  setX(x);
  setY(y);
}

void ScreenPos::lerp(ScreenPos target, int amount) {
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
