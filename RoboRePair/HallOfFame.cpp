/*
 * Bumble Bots Re-Pair, a Gamebuino game
 *
 * Copyright 2020, Erwin Bonsma
 */

#include "HallOfFame.h"

#include "Images.h"
#include "Levels.h"
#include "MainMenu.h"
#include "Music.h"
#include "ProgressTracker.h"
#include "Utils.h"

bool screenDrawn;

const uint8_t titleWidth = 16;
const uint8_t titleHeight = 3;
const uint8_t hofTitle[] = {
   4,  4,  4,  0,  6,  8,  6,  8,  6, 12, 17, 12,  6,  8,  6,  8,
  20, 22,  5, 24,  3, 12,  5,  0,  5,  5, 20, 13, 20,  8,  3, 12,
   1,  1,  1,  0,  2,  9,  3,  8,  3,  9,  1,  1,  3,  8,  2,  9
};



void updateHallOfFame() {
  music.update();
  if (gb.buttons.held(BUTTON_A, 0)) {
    showMainMenu();
  }
}

void drawHallOfFame() {
  constexpr int bufLen = 8;
  char buf[bufLen];

  if (screenDrawn) {
    // Draw only once, as screen is static and drawText is slow. The avoids CPU overload
    // when music is enabled.
    return;
  }

  gb.display.clear();

  for (int x = 0; x < titleWidth; x++) {
    for (int y = 0; y < titleHeight; y++) {
      int frameIndex = hofTitle[x + y * titleWidth];
      if (frameIndex > 0) {
        smallTilesImage.setFrame(frameIndex);
        gb.display.drawImage(16 + x * 8, y * 8, smallTilesImage);
      }
    }
  }

  gb.display.setColor(INDEX_ORANGE);
  drawText(6, 30, "hi-score:");
  snprintf(buf, bufLen, "%d", progressTracker.hiScore());
  drawText(60, 30, buf);

  for (int i = 0; i < numLevels; i++) {
    int x0 = (i / 5) * 80;
    int y0 = (i %5) * 12 + 50;

    snprintf(buf, bufLen, "%d.", (i + 1));
    drawText(x0 + 20 - textWidth(buf, 2), y0, buf, 2);

    snprintf(buf, bufLen, "%d", 9999); //progressTracker.levelHiScore(i));
    drawText(x0 + 60 - textWidth(buf, 2), y0, buf, 2);
  }

  screenDrawn = true;
}

void showHallOfFame() {
  updateFunction = updateHallOfFame;
  drawFunction = drawHallOfFame;
  screenDrawn = false;
}

