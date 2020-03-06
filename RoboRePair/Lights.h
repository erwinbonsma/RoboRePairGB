/*
 * Bumble Bots Re-Pair, a Gamebuino game
 *
 * Copyright 2020, Erwin Bonsma
 */

#include "Utils.h"

void drawDummyLight(int x, int y);
void clearDummyLights();

inline void drawLight(int x, int y, Color color) {
  gb.lights.drawPixel(x, y, color);
#ifdef DEVELOPMENT
  gb.display.setColor(color);
  drawDummyLight(x, y);
#endif
}

inline void drawLight(int x, int y, ColorIndex color) {
  gb.lights.drawPixel(x, y, color);
#ifdef DEVELOPMENT
  gb.display.setColor(color);
  drawDummyLight(x, y);
#endif
}

inline void clearLights() {
  gb.lights.clear();
#ifdef DEVELOPMENT
  clearDummyLights();
#endif
}

void drawCelebrationLights();

