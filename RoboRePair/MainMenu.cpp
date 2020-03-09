/*
 * Bumble Bots Re-Pair, a Gamebuino game
 *
 * Copyright 2020, Erwin Bonsma
 */

#include "MainMenu.h"

#include "Bot.h"
#include "Game.h"
#include "HallOfFame.h"
#include "HelpMenu.h"
#include "Images.h"
#include "Levels.h" // for GridSpec
#include "Lights.h"
#include "Music.h"
#include "Utils.h"
#include "TileGrid.h"

constexpr int numButtons = 4;
constexpr int buttonW = 14;
constexpr int buttonH = 15;

uint8_t activeButton = 1;
uint8_t clk = 0;
bool buttonsShown = false;
bool firstDraw;

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

const GridSpec titleGrid = GridSpec { .w = 12, .h = 11, .tiles = tilesTitle };
const BotSpec titleBot1 = BotSpec { .pos = GridPos(0, 0), .dir = Direction::West, .type = smallBotType };
const BotSpec titleBot2 = BotSpec { .pos = GridPos(11, 10), .dir = Direction::South, .type = smallBotType };

void highlightButton(int x0, int y0, ColorIndex iconColor = INDEX_ORANGE) {
  gb.display.setColor(INDEX_YELLOW);
  for (int x = x0 + buttonW + 2; --x >= x0; ) {
    for (int y = y0 + buttonH + 2; --y >= y0; ) {
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
  constexpr int x0 = 80 - (buttonW * numButtons + sep * (numButtons - 1)) / 2;
  for (int i = 0; i < numButtons; i++) {
    int frameIndex = i + (i == 3 && !music.isEnabled());
    buttonsImage.setFrame(frameIndex);
    int x = x0 + i * (buttonW + sep);
    gb.display.drawImage(x, 110, buttonsImage);
    if (i == activeButton) {
      highlightButton(x - 1, 109, (frameIndex < numButtons) ? INDEX_ORANGE : INDEX_BROWN);
    }
  }
}

void updateMainMenu() {
  music.update();

  grid.update();
  updateBots();

  if (!buttonsShown) {
    if (++clk < 50) {
      return;
    }
    buttonsShown = true;
  }

  if (gb.buttons.held(BUTTON_LEFT, 0)) {
    activeButton = (activeButton + numButtons - 1) % numButtons;
  }
  if (gb.buttons.held(BUTTON_RIGHT, 0)) {
    activeButton = (activeButton + 1) % numButtons;
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
        showHallOfFame();
        break;
      case 3:
        music.toggleEnabled();
        break;
      default:
        assertTrue(false);
    }
  }
}

void drawMainMenu() {
  if (firstDraw) {
    clearLights();

    // Only draw this fixed contents once, to reduce CPU load.
    gb.display.clear(INDEX_DARKGRAY);

    gb.display.setColor(INDEX_BROWN);
    gb.display.fillRoundRect(30, 1, 100, 14, 1);

    gb.display.setColor(INDEX_BLACK);
    drawText(31, 2, "eriban presents");
    drawText(46, 112, "version 0.3a");
#ifdef DEVELOPMENT
    gb.display.setColor(INDEX_RED);
    drawText(120, 112, "dev");
#endif

    firstDraw = false;
  }

  grid.draw();
  drawBots();

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

  destroyAllBots();
  grid.init(titleGrid, 8);
  addBot(titleBot1);
  addBot(titleBot2);

  updateFunction = updateMainMenu;
  drawFunction = drawMainMenu;
}

