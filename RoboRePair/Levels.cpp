/*
 * Bumble Bots Re-Pair, a Gamebuino game
 *
 * Copyright 2020, Erwin Bonsma
 */

#include "Levels.h"

const uint8_t tilesCantFail[] = {
   2,10,10,10,10,10,10,10, 8,
   0, 0, 0, 0, 0, 0, 0, 0, 0,
   0, 0, 0, 0, 0, 0, 0, 0, 0,
   0, 0, 0, 0,15, 0, 0, 0, 0,
   0, 0, 0, 0, 0, 0, 0, 0, 0,
   0, 0, 0, 0, 0, 0, 0, 0, 0,
   0, 0, 0, 0, 0, 0, 0, 0, 0
};
const BotSpec botsCantFail[] = {
  BotSpec { .pos = makeGridPos(1, 0), .dir = Direction::East },
  BotSpec { .pos = makeGridPos(7, 0), .dir = Direction::West }
};

const uint8_t tilesTest[] = {
   0, 0, 0, 0, 0, 0, 0, 0, 0,
   2,10,10,12, 0, 0,10,10, 8,
   0, 0, 0, 0, 0, 0, 0, 0, 0,
   0, 0, 0, 0,15, 0, 0, 0, 0,
   0, 0, 0, 0, 0, 0, 0, 0, 0,
   2,10,10, 0, 0, 3,10,10, 8,
   0, 0, 0, 0, 0, 0, 0, 0, 0
};
const BotSpec botsTest[] = {
  BotSpec { .pos = makeGridPos(1, 1), .dir = Direction::East },
  BotSpec { .pos = makeGridPos(7, 1), .dir = Direction::West },
  BotSpec { .pos = makeGridPos(1, 5), .dir = Direction::East },
  BotSpec { .pos = makeGridPos(7, 5), .dir = Direction::West }
};

const LevelSpec levels[numLevels] = {
  LevelSpec {
    .grid = GridSpec { .w = 9, .h = 7, .tiles = tilesTest },
    .numBots = 4,
    .bots = botsTest
  },
  LevelSpec {
    .grid = GridSpec { .w = 9, .h = 7, .tiles = tilesCantFail },
    .numBots = 2,
    .bots = botsCantFail
  }
};

