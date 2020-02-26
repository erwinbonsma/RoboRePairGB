/*
 * Bumble Bots Re-Pair, a Gamebuino game
 *
 * Copyright 2020, Erwin Bonsma
 */

#include "Utils.h"

void updateHelp() {
  // TODO
}

void drawHelp() {
  gb.display.clear();

  gb.display.setColor(INDEX_BROWN);
  drawText(6, 46, "guide them by extending");
  drawText(1, 59, "the tracks they traverse");

  drawText(13, 77, "changes the active tile");
  drawText(13, 95, "puts it on the grid when");
  drawText(3,108, "it fits and extends a path");

  gb.display.setColor(INDEX_YELLOW);
  drawText(0, 28, "re-unite (re-pair) the bots");
  drawText(2, 77, "a");
  drawText(2, 95, "b");
}

