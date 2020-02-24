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
  BotSpec { .pos = GridPos(1, 0), .dir = Direction::East },
  BotSpec { .pos = GridPos(7, 0), .dir = Direction::West }
};

const uint8_t tilesTest[] = {
   0, 0, 0, 0, 0, 0, 0, 0, 0,
   2,10,10,10,10,10,10,10, 8,
   0, 0, 0, 0, 4, 0, 0, 0, 0,
   0, 0, 0, 0, 5, 0, 0, 0, 0,
   0, 0, 0, 0, 5, 0, 0, 0, 0,
   2,10,10,10,15, 0, 0, 0, 8,
   0, 0, 0, 0, 0, 0, 0, 0, 0
};
const BotSpec botsTest[] = {
  BotSpec { .pos = GridPos(1, 1), .dir = Direction::East },
  BotSpec { .pos = GridPos(7, 1), .dir = Direction::West },
  BotSpec { .pos = GridPos(4, 3), .dir = Direction::South },
  BotSpec { .pos = GridPos(2, 5), .dir = Direction::East }
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

