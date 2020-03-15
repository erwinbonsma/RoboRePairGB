/*
 * Bumble Bots Re-Pair, a Gamebuino game
 *
 * Copyright 2020, Erwin Bonsma
 */

#include "HelpMenu.h"

#include "Images.h"
#include "MainMenu.h"
#include "Music.h"
#include "Utils.h"

bool helpDrawn;

void updateHelp() {
  music.update();
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

  drawTitleText(48, 0, "help");

  gb.display.setColor(INDEX_ORANGE);
  drawText(6, 46, "guide them by extending");
  drawText(1, 59, "the tracks they traverse");

  drawText(13, 77, "changes the active tile");
  drawText(13, 95, "puts it on the grid when");
  drawText(3,108, "it fits and extends a path");

  gb.display.setColor(INDEX_YELLOW);
  drawText(0, 28, "re-unite (re-pair) the bots");
  drawText(2, 77, "b");
  drawText(2, 95, "a");

  helpDrawn = true;
}

void showHelp() {
  updateFunction = updateHelp;
  drawFunction = drawHelp;
  helpDrawn = false;
}

