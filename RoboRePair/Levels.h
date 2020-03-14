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
  const uint8_t type;
};

struct LevelSpec {
  const char* name;
  const uint8_t numTiles;
  const uint16_t timeLimit;
  const GridSpec grid;
  const uint8_t numBots;
  const BotSpec* bots;
};

const int maxBots = 4;
const int numLevels = 10;
extern const LevelSpec levels[numLevels];
