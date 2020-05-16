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

void updateHallOfFame() {
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

  drawTitleText(20, 0, "hi-score");
  snprintf(buf, bufLen, "%d", progressTracker.hiScore());
  drawTitleText(80 - titleWidth(buf) / 2, 24, buf);

  gb.display.setColor(INDEX_ORANGE);
  drawText(20, 52, "best level scores");
  for (int i = 0; i < numLevels; i++) {
    int x0 = 5 + (i / 5) * 80;
    int y0 = (i %5) * 12 + 66;

    snprintf(buf, bufLen, "%d.", (i + 1));
    drawText(x0 + 20 - textWidth(buf, 2), y0, buf, 2);

    snprintf(buf, bufLen, "%d", progressTracker.levelHiScore(i));
    drawText(x0 + 60 - textWidth(buf, 2), y0, buf, 2);
  }

  screenDrawn = true;
}

void showHallOfFame() {
  updateFunction = updateHallOfFame;
  drawFunction = drawHallOfFame;
  screenDrawn = false;
}
