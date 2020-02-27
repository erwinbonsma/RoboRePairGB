/*
 * Bumble Bots Re-Pair, a Gamebuino game
 *
 * Copyright 2020, Erwin Bonsma
 */

#include "HelpMenu.h"

#include "Images.h"
#include "MainMenu.h"
#include "Utils.h"

bool helpDrawn;

const uint8_t logoWidth = 8;
const uint8_t logoHeight = 3;
const uint8_t helpLogo[] = {
   4,  4,  6,  8,  4,  0, 17, 12,
  20, 22, 20,  8,  5,  0, 20,  9,
   1,  1,  3,  8, 16,  8,  1,  0
};

void updateHelp() {
  if (gb.buttons.held(BUTTON_A, 0)) {
    showMainMenu();
  }
}

void drawHelp() {
  if (helpDrawn) {
    // Draw only once, as screen is static and drawText is slow. The avoids CPU overload
    // when music is enabled.
    return;
  }

  gb.display.clear();

  for (int x = 0; x < logoWidth; x++) {
    for (int y = 0; y < logoHeight; y++) {
      int frameIndex = helpLogo[x + y * logoWidth];
      if (frameIndex > 0) {
        smallTilesImage.setFrame(frameIndex);
        gb.display.drawImage(48 + x * 8, y * 8, smallTilesImage);
      }
    }
  }

  gb.display.setColor(INDEX_ORANGE);
  drawText(6, 46, "guide them by extending");
  drawText(1, 59, "the tracks they traverse");

  drawText(13, 77, "changes the active tile");
  drawText(13, 95, "puts it on the grid when");
  drawText(3,108, "it fits and extends a path");

  gb.display.setColor(INDEX_YELLOW);
  drawText(0, 28, "re-unite (re-pair) the bots");
  drawText(2, 77, "a");
  drawText(2, 95, "b");

  helpDrawn = true;
}

void showHelp() {
  updateFunction = updateHelp;
  drawFunction = drawHelp;
  helpDrawn = false;
}

