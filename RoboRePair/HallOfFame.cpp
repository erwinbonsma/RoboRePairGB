/*
 * Bumble Bots Re-Pair, a Gamebuino game
 *
 * Copyright 2020, Erwin Bonsma
 */

#include "HallOfFame.h"

#include "Levels.h"
#include "MainMenu.h"
#include "Music.h"
#include "ProgressTracker.h"
#include "Utils.h"

bool screenDrawn;

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

  gb.display.setColor(INDEX_ORANGE);
  drawText(6, 20, "hi-score:");
  snprintf(buf, bufLen, "%d", progressTracker.hiScore());
  drawText(60, 20, buf);

  for (int i = 0; i < numLevels; i++) {
    int x0 = (i / 6) * 80;
    int y0 = (i % 6) * 12 + 40;

    snprintf(buf, bufLen, "%d.", (i + 1));
    drawText(x0 + 20 - textWidth(buf), y0, buf);

    snprintf(buf, bufLen, "%d", progressTracker.levelHiScore(i));
    drawText(x0 + 60 - textWidth(buf), y0, buf);
  }

  screenDrawn = true;
}

void showHallOfFame() {
  updateFunction = updateHallOfFame;
  drawFunction = drawHallOfFame;
  screenDrawn = false;
}

