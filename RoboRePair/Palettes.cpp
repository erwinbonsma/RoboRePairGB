/*
 * Bumble Bots Re-Pair, a Gamebuino game
 *
 * Copyright 2020, Erwin Bonsma
 */

#include "Palettes.h"

const Color LBLUE = LIGHTBLUE;
const Color LGREEN = LIGHTGREEN;
const Color DGRAY = DARKGRAY;
const Color DBLUE = DARKBLUE;

// Blend of BLUE and DBLUE
const Color CUST1 = gb.createColor(34, 103, 171);

const Color palettes[numPalettes][numPaletteColors] = {
  // Default
  { BLACK,  DBLUE,  PURPLE, GREEN,  BROWN,  DGRAY,  GRAY,   WHITE,  RED,    ORANGE, YELLOW, LGREEN, LBLUE,  BLUE,   PINK,   BEIGE },
  // Game
  { DGRAY,  DBLUE,  PURPLE, GREEN,  BROWN,  BLACK,  GRAY,   WHITE,  RED,    ORANGE, YELLOW, LGREEN, LBLUE,  BLUE,   PINK,   BEIGE }
};
