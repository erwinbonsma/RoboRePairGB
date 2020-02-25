/*
 * Bumble Bots Re-Pair, a Gamebuino game
 *
 * Copyright 2020, Erwin Bonsma
 */

#include "Levels.h"

// Bot speeds (periods)
#define MEDIUM 20
#define SLOW   30

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
  BotSpec { .pos = GridPos(1, 0), .dir = Direction::East, .period = MEDIUM },
  BotSpec { .pos = GridPos(7, 0), .dir = Direction::West, .period = MEDIUM }
};

const uint8_t tilesNoChoice[] = {
   0,10, 0, 6, 0,10, 0,12, 4,
   3, 0, 5, 0,10, 0, 6, 0, 5,
   0, 9, 0, 6, 0, 9, 0,12, 5,
   5, 0, 9, 0, 6, 0,10, 0, 5,
   5, 3, 0, 5, 0,12, 0,12, 0,
   5, 0, 9, 0,12, 0, 5, 0, 5,
   1, 3, 0,10, 0, 3, 0, 3, 0
};
const BotSpec botsNoChoice[] = {
  BotSpec { .pos = GridPos(0, 5), .dir = Direction::South, .period = MEDIUM },
  BotSpec { .pos = GridPos(8, 1), .dir = Direction::North, .period = MEDIUM }
};

const uint8_t tilesSpacious[] = {
   0, 0, 0, 0, 0, 0, 0, 0, 4,
   6, 0, 0, 0, 0, 0, 0, 0, 5,
   5, 0, 0, 0, 0, 0, 0, 0, 5,
   5, 0, 0, 0,15, 0, 0, 0, 5,
   5, 0, 0, 0, 0, 0, 0, 0, 5,
   5, 0, 0, 0, 0, 0, 0, 0, 9,
   1, 0, 0, 0, 0, 0, 0, 0, 0
};
const BotSpec botsSpacious[] = {
  BotSpec { .pos = GridPos(0, 6), .dir = Direction::South, .period = MEDIUM },
  BotSpec { .pos = GridPos(8, 0), .dir = Direction::North, .period = MEDIUM }
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
  BotSpec { .pos = GridPos(1, 1), .dir = Direction::East, .period = MEDIUM },
  BotSpec { .pos = GridPos(7, 1), .dir = Direction::West, .period = MEDIUM },
  BotSpec { .pos = GridPos(4, 3), .dir = Direction::South, .period = MEDIUM },
  BotSpec { .pos = GridPos(2, 5), .dir = Direction::East, .period = MEDIUM }
};

const LevelSpec levels[numLevels] = {
  LevelSpec {
    .numTiles = 3,
    .timeLimit = 120,
    .grid = GridSpec { .w = 9, .h = 7, .tiles = tilesCantFail },
    .numBots = 2,
    .bots = botsCantFail,
  },
  LevelSpec {
    .numTiles = 1,
    .timeLimit = 120,
    .grid = GridSpec { .w = 9, .h = 7, .tiles = tilesNoChoice },
    .numBots = 2,
    .bots = botsNoChoice,
  },
  LevelSpec {
    .numTiles = 3,
    .timeLimit = 180,
    .grid = GridSpec { .w = 9, .h = 7, .tiles = tilesSpacious },
    .numBots = 2,
    .bots = botsSpacious,
  },
  LevelSpec {
    .numTiles = 3,
    .timeLimit = 120,
    .grid = GridSpec { .w = 9, .h = 7, .tiles = tilesTest },
    .numBots = 4,
    .bots = botsTest,
  }
};

