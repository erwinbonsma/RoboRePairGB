/*
 * Bumble Bots Re-Pair, a Gamebuino game
 *
 * Copyright 2020, Erwin Bonsma
 */

#include <Gamebuino-Meta.h>

class ScreenPos {
  int16_t _x;
  int16_t _y;

public:
  int getX() { return _x >> 4; }
  int getY() { return _y >> 4; }

  void lerp(ScreenPos target, uint16_t amount);

  ScreenPos(int x, int y);
};

void assertFailed(const char *function, const char *file, int lineNo, const char *expression);

#define assertTrue(condition) \
if (!(condition)) { \
  assertFailed(__func__, __FILE__, __LINE__, #condition); \
}
