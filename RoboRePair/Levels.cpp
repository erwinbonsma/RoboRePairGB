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

const uint8_t tilesDetour[] = {
   0, 0, 0, 0, 6, 0, 0, 0, 0,
   0, 0, 0, 0, 5, 0, 0, 0, 0,
   0, 0, 0, 0, 1, 0, 0, 0, 0,
   0,15, 0, 3,10,12, 0,15, 0,
   0, 0, 0, 0, 4, 0, 0, 0, 0,
   0, 0, 0, 0, 5, 0, 0, 0, 0,
   0, 0, 0, 0, 9, 0, 0, 0, 0
};
const BotSpec botsDetour[] = {
  BotSpec { .pos = GridPos(4, 0), .dir = Direction::West, .period = SLOW },
  BotSpec { .pos = GridPos(4, 6), .dir = Direction::East, .period = SLOW }
};

const uint8_t tilesDeathValley[] = {
   0, 0, 0, 0, 0,10,10,10,12,
   0, 0, 0, 0, 0, 0, 0, 0, 1,
   0, 0, 0, 0, 0, 0, 0, 0, 0,
   0, 0, 0, 9, 0, 3, 0, 0, 0,
   0, 0, 0,12, 0, 6, 0, 0, 0,
   0, 0, 0, 0, 0, 0, 0, 0, 0,
   4, 0, 0, 0, 0, 0, 0, 0, 0,
   3,10,10,10, 0, 0, 0, 0, 0
};
const BotSpec botsDeathValley[] = {
  BotSpec { .pos = GridPos(0, 7), .dir = Direction::West, .period = MEDIUM },
  BotSpec { .pos = GridPos(8, 0), .dir = Direction::East, .period = MEDIUM }
};

const uint8_t tilesFourOfAKind[] = {
   6,10,10,12, 0, 0, 0, 2,12,
   1, 0, 0, 0, 0, 0, 0, 0, 5,
   0, 0, 0, 0, 0, 0, 0, 0, 5,
   0, 0, 0, 0,13, 0, 0, 0, 9,
   6, 0, 0, 0, 7, 0, 0, 0, 0,
   5, 0, 0, 0, 0, 0, 0, 0, 0,
   5, 0, 0, 0, 0, 0, 0, 0, 4,
   3, 8, 0, 0, 0, 3,10,10, 9
};
const BotSpec botsFourOfAKind[] = {
  BotSpec { .pos = GridPos(2, 0), .dir = Direction::West, .period = MEDIUM },
  BotSpec { .pos = GridPos(8, 2), .dir = Direction::North, .period = MEDIUM },
  BotSpec { .pos = GridPos(6, 7), .dir = Direction::East, .period = MEDIUM },
  BotSpec { .pos = GridPos(0, 5), .dir = Direction::South, .period = MEDIUM }
};

const uint8_t tilesTest[] = {
   0, 0, 0, 0, 0, 0, 0, 0, 0,
   2,10,10,10,10,10,10,10, 8,
   0, 0, 0, 0, 4, 0, 0, 0, 0,
   0, 0, 0, 0, 5, 0, 0, 0, 0,
   0, 0, 0, 0, 5, 0, 0, 0, 4,
   2,10,10,10, 9, 0, 0, 2, 0,
   0, 0, 0, 0, 0, 0, 0, 0, 1
};
const BotSpec botsTest[] = {
  BotSpec { .pos = GridPos(1, 1), .dir = Direction::East, .period = MEDIUM },
  BotSpec { .pos = GridPos(7, 1), .dir = Direction::West, .period = MEDIUM },
  BotSpec { .pos = GridPos(4, 3), .dir = Direction::South, .period = MEDIUM },
  BotSpec { .pos = GridPos(2, 5), .dir = Direction::East, .period = MEDIUM }
};

const uint8_t tilesTwist[] = {
   0, 0, 0, 0, 0,10, 0, 0, 0,
   0, 0, 0, 0, 0, 4, 0, 0, 0,
   0, 0, 0, 0, 0, 5, 0, 0, 0,
   0, 0, 0, 0, 6,15, 0, 0, 0,
   0, 0, 0, 0,15, 9, 0, 0, 0,
   0, 0, 0, 0, 5, 0, 0, 0, 0,
   0, 0, 0, 0, 1, 0, 0, 0, 0,
   0, 0, 0, 0,10, 0, 0, 0, 0
};
const BotSpec botsTwist[] = {
  BotSpec { .pos = GridPos(5, 1), .dir = Direction::North, .period = MEDIUM },
  BotSpec { .pos = GridPos(4, 6), .dir = Direction::South, .period = MEDIUM },
};

const uint8_t tilesObstructions[] = {
   0, 0, 0, 0, 0, 0, 0, 0, 4,
   0, 0, 0, 0, 0, 0, 9, 0, 5,
   0, 0, 3, 0, 0, 0, 0, 0, 5,
   0, 0, 0, 0, 0, 0, 5, 0, 9,
   6, 0, 5, 0, 0, 0, 0, 0, 0,
   5, 0, 0, 0, 0, 0,12, 0, 0,
   5, 0, 6, 0, 0, 0, 0, 0, 0,
   1, 0, 0, 0, 0, 0, 0, 0, 0,
};
const BotSpec botsObstructions[] = {
  BotSpec { .pos = GridPos(0, 5), .dir = Direction::South, .period = MEDIUM },
  BotSpec { .pos = GridPos(8, 2), .dir = Direction::North, .period = MEDIUM },
};


const LevelSpec levels[numLevels] = {
  LevelSpec {
    .numTiles = 3,
    .timeLimit = 45,
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
    .timeLimit = 240,
    .grid = GridSpec { .w = 9, .h = 7, .tiles = tilesSpacious },
    .numBots = 2,
    .bots = botsSpacious,
  },
  LevelSpec {
    .numTiles = 3,
    .timeLimit = 240,
    .grid = GridSpec { .w = 9, .h = 7, .tiles = tilesDetour },
    .numBots = 2,
    .bots = botsDetour,
  },
  LevelSpec {
    .numTiles = 3,
    .timeLimit = 240,
    .grid = GridSpec { .w = 9, .h = 8, .tiles = tilesDeathValley },
    .numBots = 2,
    .bots = botsDeathValley,
  },
  LevelSpec {
    .numTiles = 3,
    .timeLimit = 240,
    .grid = GridSpec { .w = 9, .h = 8, .tiles = tilesTwist },
    .numBots = 2,
    .bots = botsTwist,
  },
  LevelSpec {
    .numTiles = 3,
    .timeLimit = 240,
    .grid = GridSpec { .w = 9, .h = 8, .tiles = tilesObstructions },
    .numBots = 2,
    .bots = botsObstructions,
  },
  LevelSpec {
    .numTiles = 3,
    .timeLimit = 240,
    .grid = GridSpec { .w = 9, .h = 8, .tiles = tilesFourOfAKind },
    .numBots = 4,
    .bots = botsFourOfAKind,
  },
};

