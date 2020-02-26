/*
 * Bumble Bots Re-Pair, a Gamebuino game
 *
 * Copyright 2020, Erwin Bonsma
 */

#include <Gamebuino-Meta.h>

#include "Utils.h"

const uint8_t numPalettes = 2;

const uint8_t PALETTE_DEFAULT = 0;
const uint8_t PALETTE_GAME = 1;

const uint8_t numPaletteColors = 16;
extern const Color palettes[numPalettes][numPaletteColors];
