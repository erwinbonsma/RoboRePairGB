/*
 * Bumble Bots Re-Pair, a Gamebuino game
 *
 * Copyright 2020, Erwin Bonsma
 */

#ifndef UTILS_H
#define UTILS_H

#include <Gamebuino-Meta.h>

#define CALL_MEMBER_FN(object, ptrToMember)  ((object).*(ptrToMember))

struct Vector2D {
  int8_t x;
  int8_t y;
};

typedef Vector2D GridPos;

enum class Direction : uint8_t {
  North = 0,
  East = 1,
  South = 2,
  West = 3
};

inline Direction clkwise(Direction dir) { return (Direction)(((int)dir + 1) % 4); }
inline Direction cclkwise(Direction dir) { return (Direction)(((int)dir + 3) % 4); }
inline Direction opposite(Direction dir) { return (Direction)(((int)dir + 2) % 4); }

extern const Vector2D dirVectors[4];

int orientation(Vector2D v1, Vector2D v2);

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
