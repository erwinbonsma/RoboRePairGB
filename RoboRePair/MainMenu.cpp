/*
 * Bumble Bots Re-Pair, a Gamebuino game
 *
 * Copyright 2020, Erwin Bonsma
 */

#include "MainMenu.h"

#include "Images.h"

uint8_t activeButton = 1;
bool musicOn = true;

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

void highlightButton(int x0, int y0, ColorIndex iconColor = INDEX_ORANGE) {
  gb.display.setColor(INDEX_YELLOW);
  for (int x = x0 + 15; --x >= x0; ) {
    for (int y = y0 + 17; --y >= y0; ) {
      if (
        gb.display.getPixelIndex(x, y)==INDEX_BLACK && (
          gb.display.getPixelIndex(x + 1, y) == iconColor ||
          gb.display.getPixelIndex(x - 1, y) == iconColor ||
          gb.display.getPixelIndex(x, y + 1) == iconColor ||
          gb.display.getPixelIndex(x, y - 1) == iconColor
        )
      ) {
        gb.display.drawPixel(x, y);
      }
    }
  }
}

void updateMainMenu() {
  if (gb.buttons.held(BUTTON_LEFT, 0)) {
    activeButton = (activeButton + 2) % 3;
  }
  if (gb.buttons.held(BUTTON_RIGHT, 0)) {
    activeButton = (activeButton + 1) % 3;
  }
  if (gb.buttons.held(BUTTON_A, 0)) {
    if (activeButton == 2) {
      musicOn = !musicOn;
    }
  }
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
    int frameIndex = i + (i == 2 && !musicOn);
    buttonsImage.setFrame(frameIndex);
    int x = x0 + i * (15 + sep);
    gb.display.drawImage(x, 108, buttonsImage);
    if (i == activeButton) {
      highlightButton(x - 1, 107, (frameIndex < 3) ? INDEX_ORANGE : INDEX_BROWN);
    }
  }
}

