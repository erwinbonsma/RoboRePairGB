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
  const uint8_t period;
};

struct LevelSpec {
  const uint8_t numTiles;
  const uint8_t timeLimit;
  const GridSpec grid;
  const uint8_t numBots;
  const BotSpec* bots;
};

const int maxBots = 4;
const int numLevels = 9;
extern const LevelSpec levels[numLevels];
