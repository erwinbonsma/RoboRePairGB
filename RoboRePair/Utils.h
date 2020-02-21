/*
 * Bumble Bots Re-Pair, a Gamebuino game
 *
 * Copyright 2020, Erwin Bonsma
 */

#include <Gamebuino-Meta.h>

#ifndef UTILS_H
#define UTILS_H

struct GridPos {
  uint8_t x;
  uint8_t y;
};

enum class Direction : uint8_t {
  North = 0,
  East = 1,
  South = 2,
  West = 3
};

Direction clkwise(Direction dir);
Direction cclkwise(Direction dir);
Direction opposite(Direction dir);

extern int8_t dx[4];
extern int8_t dy[4];

class ScreenPos {
  int16_t _x;
  int16_t _y;

public:
  int getX() const { return _x >> 4; }
  int getY() const { return _y >> 4; }

  void lerp(ScreenPos target, uint16_t amount);

  ScreenPos(int x, int y);
};

void assertFailed(const char *function, const char *file, int lineNo, const char *expression);

#define assertTrue(condition) \
if (!(condition)) { \
  assertFailed(__func__, __FILE__, __LINE__, #condition); \
}

#endif
