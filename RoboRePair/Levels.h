/*
 * Bumble Bots Re-Pair, a Gamebuino game
 *
 * Copyright 2020, Erwin Bonsma
 */

#include "Utils.h"

struct GridSpec {
  const uint8_t w;
  const uint8_t h;
  const uint8_t* tiles;
};

struct BotSpec {
  const GridPos pos;
  const Direction dir;
};

struct LevelSpec {
  const GridSpec grid;
  const uint8_t numBots;
  const BotSpec* bots;
};

const int maxBots = 2;
const int numLevels = 2;
extern const LevelSpec levels[numLevels];
