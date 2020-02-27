/*
 * Bumble Bots Re-Pair, a Gamebuino game
 *
 * Copyright 2020, Erwin Bonsma
 */

#include "MainMenu.h"

#include "Images.h"

const uint8_t w = 12;
const uint8_t h = 11;
const uint8_t tilesTitle[] = {
  17, 12,  4,  4,  6, 14, 12, 17, 12,  4,  6,  8,
  20, 13,  5,  5,  5,  5,  5, 20, 13,  5, 20,  8,
  16, 13,  3, 13,  1,  5,  1, 20,  9, 20, 11,  8,
   0,  7, 14, 11, 10, 11, 10, 11, 14, 11, 12,  0,
   0,  5, 20, 12,  6, 14, 21,  8,  7,  8,  5,  0,
   0,  5, 20, 13,  5,  5,  5,  0,  3, 12,  5,  0,
   0,  5, 16,  9,  7,  9,  5,  0,  2,  9,  5,  0,
   0,  7, 14, 10, 11, 14, 11, 14, 10, 14, 13,  0,
  17, 13,  7,  8,  0, 20, 12,  7, 12,  5, 20, 12,
  20, 13, 20,  8, 24, 20,  9, 20, 22,  5, 20, 13,
   1,  1,  3,  8,  0,  1,  0,  1,  1,  1,  1,  1
};

void updateMainMenu() {
  // TODO
}

void drawMainMenu() {
  gb.display.clear();
  for (int x = 0; x < w; x++) {
    for (int y = 0; y < h; y++) {
      int v = tilesTitle[x + y * w];
      if (v > 0) {
        smallTilesImage.setFrame(v);
        gb.display.drawImage(32 + x * 8, y * 8 + 12, smallTilesImage);
      }
    }
  }

  int sep = 16;
  int x0 = 80 - (15 * 3 + sep * 2) / 2;
  for (int i = 0; i < 3; i++) {
    buttonsImage.setFrame(i);
    gb.display.drawImage(x0 + i * (15 + sep), 108, buttonsImage);
  }
}

