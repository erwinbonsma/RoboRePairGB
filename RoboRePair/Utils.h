/*
 * Bumble Bots Re-Pair, a Gamebuino game
 *
 * Copyright 2020, Erwin Bonsma
 */

#ifndef UTILS_H
#define UTILS_H

#include <Gamebuino-Meta.h>

#define DEVELOPMENT
#ifdef DEVELOPMENT
//#define SCREEN_RECORDING
#endif

#define CALL_MEMBER_FN(object, ptrToMember)  ((object).*(ptrToMember))

typedef void (*UpdateFunction)();
typedef void (*DrawFunction)();

// Defined in .ino file. Declared here for convenience
extern UpdateFunction updateFunction;
extern DrawFunction drawFunction;

const int fps = 25;

inline int sgn(int val) {
  return (val > 0) - (val < 0);
}

struct Vector2D {
  int8_t x;
  int8_t y;

  Vector2D() = default;
  Vector2D(const Vector2D& v) { x = v.x; y = v.y; }
  Vector2D(int xVal, int yVal) { x = (int8_t)xVal; y = (int8_t)yVal; }

  void add(Vector2D v) { x += v.x; y += v.y; }
};

inline bool operator==(const Vector2D &lhs, const Vector2D &rhs) {
  return (lhs.x == rhs.x && lhs.y == rhs.y);
}
inline bool operator!=(const Vector2D &lhs, const Vector2D &rhs) {
  return !(lhs == rhs);
}

typedef Vector2D GridPos;

extern const GridPos GRIDPOS_NONE;

enum class Direction : uint8_t {
  North = 0,
  East = 1,
  South = 2,
  West = 3,

  // Special cases:
  None = 16,
  Multiple = 17
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

  void setX(int x) { _x = (int16_t)(x << 4) + 8; }
  void setY(int y) { _y = (int16_t)(y << 4) + 8; }

  // amount = [0..256]
  void lerp(ScreenPos target, int amount);

  ScreenPos() = default;
  ScreenPos(int x, int y) { setX(x); setY(y); }
  ScreenPos(const ScreenPos& pos) { _x = pos._x; _y = pos._y; }

  void add(Vector2D v) { _x += (v.x << 4); _y += (v.y << 4); }
};

void drawText(int x, int y, const char* s, int sep = 1);
int textWidth(const char* s);

void assertFailed(const char *function, const char *file, int lineNo, const char *expression);

#define assertTrue(condition) \
if (!(condition)) { \
  assertFailed(__func__, __FILE__, __LINE__, #condition); \
}

#endif
