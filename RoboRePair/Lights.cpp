/*
 * Bumble Bots Re-Pair, a Gamebuino game
 *
 * Copyright 2020, Erwin Bonsma
 */

#include "Lights.h"

void drawDummyLight(int x, int y) {
  gb.display.drawFastVLine(x * 159, y * 32, 32);
}

void clearDummyLights() {
  gb.display.setColor(INDEX_BLACK);
  gb.display.drawFastVLine(0, 0, 128);
  gb.display.drawFastVLine(159, 0, 128);
}

constexpr uint8_t numGradientColors = 36;
const uint16_t gradientColors[numGradientColors] = {
  0xf800, 0xf940, 0xfaa0, 0xfbe0, 0xfd40, 0xfea0,
  0xffe0, 0xd7e0, 0xafe0, 0x7fe0, 0x57e0, 0x2fe0,
  0x07e0, 0x07e5, 0x07ea, 0x07ef, 0x07f5, 0x07fa,
  0x07ff, 0x06bf, 0x055f, 0x03ff, 0x02bf, 0x015f,
  0x001f, 0x281f, 0x501f, 0x781f, 0xa81f, 0xd01f,
  0xf81f, 0xf81a, 0xf815, 0xf80f, 0xf80a, 0xf805,
};

/* Lights animation.
 *
 * Two "chains" of 4-lights circle the console clockwise. The chains are both
 * a single color which continuously changes. Both chain colors are always at
 * opposite ends of the color gradient.
 *
 * Implementation copied from my earlier Bumble Bots game.
 */
void drawCelebrationLights() {
  // Vary color of chains over time
  for (int i = 8; --i >= 0; ) {
    int x = (i < 4) ? 0 : 1;
    int y = (i < 4) ? i : 7 - i;
    // The "chain" that is currently occupying this light-pixel
    uint8_t chain = ((i + gb.frameCount / 2) / 4) % 2;
    uint8_t chainColorIndex =
      (gb.frameCount / 4 + chain * (numGradientColors / 2)) % numGradientColors;
    drawLight(x, y, (Color)gradientColors[chainColorIndex]);
  }
}

