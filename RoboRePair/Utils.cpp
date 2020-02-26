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
  {6,  6,23,17,12,29,17}, // a
  {6, 22,23,19,12,13, 9},
  {6,  6,21, 3,24, 0,24},
  {6, 22,21,19,12,21, 9},
  {6, 6,23, 3,24,24,24},
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
  {6,  6,21, 3,12,21,25},
  {6, 22,23,17,12,13,17},
  {6,  6, 3,18,24,12, 9},
  {9, -4, 2, 0, 0,30,21,17, 8,-4},
  {6, 20,21, 3,20,21,25}, // u
  {6, 20,21, 3,20,21, 9},
  {9, 20,21, 3,20,21,11,20,21, 9},
  {6, 20, 7,17,20,13,17},
  {6, 20, 3,18,20,29, 9},
  {6, 18, 6,19,28, 9,24}, // z
  {0}, // space
  {4, -2,0,26,-2}, // -
  {4, 6,21,3,-2},  // (
  {4, -2,12,21,9}, // )
  {2, 0,31},       // +
  {3, 16,0,16},    // :
  {3, 20,21,16},    // !
  {4, -2,0,0,9},   // ,
};
// Could speed text drawing up a bit by ordering characters by usage
const char* fontChars = "abcdefghijklmnopqrstuvwxyz -()+:!,";

const int8_t* fontSpecForChar(char ch) {
  const char* p = fontChars;
  while (*p && *p != ch) {
    ++p;
  }
  assertTrue(*p == ch);
  return fontSpec[p - fontChars];
}

void drawText(int x, int y, const char* s, ColorIndex color) {
  const char* p = s;
  while (*p) {
    const int8_t* fontSpec = fontSpecForChar(*p);
    int row = 0;
    int len = fontSpec[0];
    // Draw character
    for (int i = 1; i <= len; ++i) {
      int v = fontSpec[i];
      if (v < 0) {
        x += v + 2; // Tweak spacing
      } else {
        if (row == 3) {
          row = 0;
          x += 4;
        }

        // Draw glyph
        if (v & 0x01) {
          gb.display.drawPixel(x + 1, y     + row * 4, color);
          gb.display.drawPixel(x + 2, y     + row * 4, color);
        }
        if (v & 0x02) {
          gb.display.drawPixel(x + 3, y + 1 + row * 4, color);
          gb.display.drawPixel(x + 3, y + 2 + row * 4, color);
        }
        if (v & 0x04) {
          gb.display.drawPixel(x + 1, y + 3 + row * 4, color);
          gb.display.drawPixel(x + 2, y + 3 + row * 4, color);
        }
        if (v & 0x08) {
          gb.display.drawPixel(x    , y + 1 + row * 4, color);
          gb.display.drawPixel(x    , y + 2 + row * 4, color);
        }
        if (v & 0x10) {
          gb.display.drawPixel(x + 1, y + 1 + row * 4, color);
          gb.display.drawPixel(x + 1, y + 2 + row * 4, color);
          gb.display.drawPixel(x + 2, y + 1 + row * 4, color);
          gb.display.drawPixel(x + 2, y + 2 + row * 4, color);
        }
        row += 1;
      }
    }
    x += 3;
    ++p;
  }
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
