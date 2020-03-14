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

const GridPos GRIDPOS_NONE = GridPos(-1, -1);


void ScreenPos::lerp(ScreenPos target, int amount) {
  assertTrue(amount <= 256);
  _x = (_x * (256 - amount) + target._x * amount) >> 8;
  _y = (_y * (256 - amount) + target._y * amount) >> 8;
}

const int8_t fontSpec[][26] = {
  // Put digits at front (as score is drawn during game play)
  {6, 6,23,3,12,29,9},    // 0
  {5, -2,28,21,27,-2},    // 1
  {6, 18, 6,19,12,9,24},  // 2
  {6, 18,18,18,12,13,9},  // 3
  {6, 20,19,0,20,29,17},  // 4
  {6, 22,19,18,24,12,9},  // 5
  {6, 6,23,3,24,12,9},    // 6
  {6, 18,0,0,28,21,17},   // 7
  {6, 6,7,3,12,13,9},     // 8
  {6, 6,3,18,12,29,9},    // 9
  // Next put common characters
  {6, 6,23, 3,24,24,24},  // e
  {6, 22,23,17,12,13,17}, // r
  {9, -5, 2, 0, 0,30,21,17, 8,-5}, // t
  {6,  6, 3,18,24,12, 9}, // s
  {6,  6,23,17,12,29,17}, // a
  {6, 22,23,19,12,13, 9},
  {6,  6,21, 3,24, 0,24},
  {6, 22,21,19,12,21, 9},
  {6, 22,23,17,24,24, 0}, // f
  {6, 6,21, 3,24,28, 9},
  {6, 20,23,17,20,29,17},
  {3, 20,21,17},
  {6,  0, 0, 3,20,21, 9},
  {6, 20,23,17,20,13,17}, // k
  {6, 20,21,19, 0, 0,24},
  {9, 22,21,17,14,21,17,12,21,17},
  {6, 22,21,17,12,21,17},
  {6,  6,21, 3,12,21, 9},
  {5, 22,23,17,12, 9}, // p
  {6,  6,21, 3,12,21,25}, // q
  {6, 20,21, 3,20,21,25}, // u
  {6, 20,21, 3,20,21, 9},
  {9, 20,21, 3,20,21,11,20,21, 9},
  {6, 20, 7,17,20,13,17},
  {6, 20, 3,18,20,29, 9},
  {6, 18, 6,19,28, 9,24}, // z
  {0}, // space
  {3, -2,0,24}, // -
  {7, 6,21,3,8,0,8,-5},  // (
  {7, -5,2,0,2,12,21,9}, // )
  {2, 0,31},       // +
  {3, 16,0,16},    // :
  {3, 20,21,16},   // !
  {4, -2,0,0,9},   // ,
  {3, 0,0,16},     // .
  {1, 20},         // '
  {5, 6,6,16,12,9} // ?
};
// Could speed text drawing up a bit by ordering characters by usage
const char* fontChars = "0123456789ertsabcdfghijklmnopquvwxyz -()+:!,.'?";

const int8_t* fontSpecForChar(char ch) {
  const char* p = fontChars;
  while (*p && *p != ch) {
    ++p;
  }
  assertTrue(*p == ch);
  return fontSpec[p - fontChars];
}

void drawText(int x0, int y0, const char* s, int sep) {
  const char* p = s;
  int x = x0;
  while (*p) {
    const int8_t* fontSpec = fontSpecForChar(*p);
    int row = 0;
    // fontSpec[0] is the number of glyphs + spacing tweaks
    const int8_t* endP = fontSpec + *fontSpec;
    // Draw character
    while (++fontSpec <= endP) {
      int v = *fontSpec;
      if (v < 0) {
        x += v + 3; // Tweak spacing
      } else {
        if (row == 3) {
          row = 0;
          x += 4;
        }

        // Draw glyph
        // Note: Using _drawPixel instead of drawPixel for performance. The latter only redirects to
        // the former anyway.
        int y = y0 + 4 * row;
        if (v & 0x01) {
          gb.display._drawPixel(x + 1, y);
          gb.display._drawPixel(x + 2, y);
        }
        if (v & 0x02) {
          gb.display._drawPixel(x + 3, y + 1);
          gb.display._drawPixel(x + 3, y + 2);
        }
        if (v & 0x04) {
          gb.display._drawPixel(x + 1, y + 3);
          gb.display._drawPixel(x + 2, y + 3);
        }
        if (v & 0x08) {
          gb.display._drawPixel(x    , y + 1);
          gb.display._drawPixel(x    , y + 2);
        }
        if (v & 0x10) {
          gb.display._drawPixel(x + 1, y + 1);
          gb.display._drawPixel(x + 1, y + 2);
          gb.display._drawPixel(x + 2, y + 1);
          gb.display._drawPixel(x + 2, y + 2);
        } else {
          if ((v & 0x03) == 0x03) {
            gb.display._drawPixel(x + 2, y + 1);
          }
          if ((v & 0x06) == 0x06) {
            gb.display._drawPixel(x + 2, y + 2);
          }
          if ((v & 0x0c) == 0x0c) {
            gb.display._drawPixel(x + 1, y + 2);
          }
          if ((v & 0x09) == 0x09) {
            gb.display._drawPixel(x + 1, y + 1);
          }
        }

        row += 1;
      }
    }
    x += 2 + sep;
    ++p;
  }
}

int textWidth(const char* s, int sep) {
  const char* p = s;
  int w = 0;
  while (*p) {
    const int8_t* fontSpec = fontSpecForChar(*p);
    int row = 0;
    int len = fontSpec[0];
    for (int i = 1; i <= len; ++i) {
      int v = fontSpec[i];
      if (v < 0) {
        w += v + 3;
      } else {
        if (row == 3) {
          row = 0;
          w += 4;
        }
        row += 1;
      }
    }
    w += 2 + sep;
    ++p;
  }
  if (p != s) {
    w += 1; // Also leave one pixel spacing at the end
  }
  return w;
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
      gb.display.setColor(INDEX_RED);
      gb.display.println("Assert failed:");
      gb.display.println(function);
      gb.display.println(file);
      gb.display.println(lineNo, DEC);
      gb.display.println(expression);
    }
  }
}
