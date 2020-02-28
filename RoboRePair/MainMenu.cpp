/*
 * Bumble Bots Re-Pair, a Gamebuino game
 *
 * Copyright 2020, Erwin Bonsma
 */

#include "MainMenu.h"

#include "Game.h"
#include "HelpMenu.h"
#include "Images.h"
#include "Music.h"
#include "Utils.h"

uint8_t activeButton = 1;
uint8_t clk = 0;
bool buttonsShown = false;
bool firstDraw;

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
        gb.display.getPixelIndex(x, y)==INDEX_DARKGRAY && (
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

void drawButtons() {
  constexpr int sep = 16;
  constexpr int x0 = 80 - (15 * 3 + sep * 2) / 2;
  for (int i = 0; i < 3; i++) {
    int frameIndex = i + (i == 2 && !music.isEnabled());
    buttonsImage.setFrame(frameIndex);
    int x = x0 + i * (15 + sep);
    gb.display.drawImage(x, 110, buttonsImage);
    if (i == activeButton) {
      highlightButton(x - 1, 109, (frameIndex < 3) ? INDEX_ORANGE : INDEX_BROWN);
    }
  }
}

void updateMainMenu() {
  music.update();
  
  if (!buttonsShown) {
    if (++clk < 50) {
      return;
    }
    buttonsShown = true;
  }

  if (gb.buttons.held(BUTTON_LEFT, 0)) {
    activeButton = (activeButton + 2) % 3;
  }
  if (gb.buttons.held(BUTTON_RIGHT, 0)) {
    activeButton = (activeButton + 1) % 3;
  }
  if (gb.buttons.held(BUTTON_A, 0)) {
    switch (activeButton) {
      case 0:
        showHelp();
        break;
      case 1:
        startGame();
        break;
      case 2:
        music.toggleEnabled();
        break;
      default:
        assertTrue(false);
    }
  }
}

void drawMainMenu() {
  if (firstDraw) {
    // Only draw this fixed contents once, to reduce CPU load.
    gb.display.clear(INDEX_DARKGRAY);

    gb.display.setColor(INDEX_BROWN);
    gb.display.fillRoundRect(30, 1, 100, 14, 1);

    gb.display.setColor(INDEX_BLACK);
    drawText(31, 2, "eriban presents");
    drawText(46, 112, "version 0.1");

    firstDraw = false;
  }

  // Draw Title
  for (int x = 0; x < w; x++) {
    for (int y = 0; y < h; y++) {
      int v = tilesTitle[x + y * w];
      smallTilesImage.setFrame(v);
      gb.display.drawImage(32 + x * 8, y * 8 + 19, smallTilesImage);
    }
  }
  gb.display.drawImage(35, 45, titleResistor1Image);
  gb.display.drawImage(35, 58, titleResistor2Image);
  gb.display.drawImage(35, 71, titleResistor1Image);
  gb.display.drawImage(121, 45, titleImpedanceImage);
  gb.display.drawImage(122, 58, titleResistor1Image);
  gb.display.drawImage(121, 71, titleImpedanceImage);
  gb.display.drawImage(90, 59, titleICImage);
  gb.display.drawImage(90, 68, titleICImage);
  gb.display.drawImage(65, 85, titleCapacitor1Image);
  gb.display.drawImage(80, 100, titleCapacitor2Image);
  gb.display.drawImage(84, 97, titleCapacitor2Image);

  if (buttonsShown) {
    // Clear display buffer where buttons are drawn
    memset(gb.display._buffer + (40 * 109), (int)INDEX_DARKGRAY | ((int)INDEX_DARKGRAY << 4), 80 * 17);
    drawButtons();
  }
}

void showMainMenu() {
  music.start();
  firstDraw = true;

  updateFunction = updateMainMenu;
  drawFunction = drawMainMenu;
}

