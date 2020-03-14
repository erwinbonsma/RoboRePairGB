/*
 * Bumble Bots Re-Pair, a Gamebuino game
 *
 * Copyright 2020, Erwin Bonsma
 */

#include "Levels.h"

#include "Bot.h"

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
  BotSpec { .pos = GridPos(1, 0), .dir = Direction::East, .type = normalBotType },
  BotSpec { .pos = GridPos(7, 0), .dir = Direction::West, .type = normalBotType }
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
  BotSpec { .pos = GridPos(0, 5), .dir = Direction::South, .type = normalBotType },
  BotSpec { .pos = GridPos(8, 1), .dir = Direction::North, .type = normalBotType }
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
  BotSpec { .pos = GridPos(0, 6), .dir = Direction::South, .type = normalBotType },
  BotSpec { .pos = GridPos(8, 0), .dir = Direction::North, .type = normalBotType }
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
  BotSpec { .pos = GridPos(4, 0), .dir = Direction::West, .type = slowBotType },
  BotSpec { .pos = GridPos(4, 6), .dir = Direction::East, .type = slowBotType }
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
  BotSpec { .pos = GridPos(0, 7), .dir = Direction::West, .type = normalBotType },
  BotSpec { .pos = GridPos(8, 0), .dir = Direction::East, .type = normalBotType }
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
  BotSpec { .pos = GridPos(2, 0), .dir = Direction::West, .type = normalBotType },
  BotSpec { .pos = GridPos(8, 2), .dir = Direction::North, .type = normalBotType },
  BotSpec { .pos = GridPos(6, 7), .dir = Direction::East, .type = normalBotType },
  BotSpec { .pos = GridPos(0, 5), .dir = Direction::South, .type = normalBotType }
};

const uint8_t tilesTwoPair[] = {
   6,10,10,10,14,10,10,10,12,
   5, 0, 0, 0, 0, 0, 0, 0, 5,
   5, 0, 0, 0, 0, 0, 0, 0, 5,
   7, 0, 0, 0, 7, 0, 0, 0, 5,
   5, 0, 0, 0,13, 0, 0, 0,13,
   5, 0, 0, 0, 0, 0, 0, 0, 5,
   5, 0, 0, 0, 0, 0, 0, 0, 5,
   3,10,10,10,11,10,10,10, 9
};
const BotSpec botsTwoPair[] = {
  BotSpec { .pos = GridPos(3, 0), .dir = Direction::West, .type = normalBotType },
  BotSpec { .pos = GridPos(8, 3), .dir = Direction::North, .type = normalPinkBotType },
  BotSpec { .pos = GridPos(5, 7), .dir = Direction::East, .type = normalBotType },
  BotSpec { .pos = GridPos(0, 4), .dir = Direction::South, .type = normalPinkBotType }
};

const uint8_t tilesQueue[] = {
   0, 0, 0, 0,14, 0, 0, 0, 0,
   0, 0, 0, 0, 5, 0, 0, 0, 0,
   0, 0, 0, 0,15, 0, 0, 0, 0,
   0, 0, 0, 0, 5, 0, 0, 0, 0,
   0, 0, 7,10,11,10,13, 0, 0,
   0, 0, 0, 0, 0, 0, 0, 0, 0,
   0, 0, 0, 0, 0, 0, 0, 0, 0,
   0, 0, 0, 0, 0, 0, 0, 0, 0
};
const BotSpec botsQueue[] = {
  BotSpec { .pos = GridPos(4, 1), .dir = Direction::South, .type = slowBotType },
  BotSpec { .pos = GridPos(4, 2), .dir = Direction::South, .type = slowBlueBotType },
  BotSpec { .pos = GridPos(4, 3), .dir = Direction::South, .type = slowBotType },
  BotSpec { .pos = GridPos(4, 4), .dir = Direction::South, .type = slowBlueBotType }
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
  BotSpec { .pos = GridPos(1, 1), .dir = Direction::East, .type = normalBotType },
  BotSpec { .pos = GridPos(7, 1), .dir = Direction::West, .type = normalBotType },
  BotSpec { .pos = GridPos(4, 3), .dir = Direction::South, .type = normalBotType },
  BotSpec { .pos = GridPos(2, 5), .dir = Direction::East, .type = normalBotType }
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
  BotSpec { .pos = GridPos(5, 1), .dir = Direction::North, .type = normalBotType },
  BotSpec { .pos = GridPos(4, 6), .dir = Direction::South, .type = normalBotType },
};

const uint8_t tilesCramped[] = {
   0, 0, 0, 0, 0, 0, 6, 8,
   0, 0, 0, 0, 0, 0, 3,12,
   0, 0, 0, 0, 0, 0, 0, 9,
   0, 0, 0, 9, 3, 0, 0, 0,
   0, 0, 0,12, 6, 0, 0, 0,
   6, 0, 0, 0, 0, 0, 0, 0,
   3,12, 0, 0, 0, 0, 0, 0,
   2, 9, 0, 0, 0, 0, 0, 0
};
const BotSpec botsCramped[] = {
  BotSpec { .pos = GridPos(0, 5), .dir = Direction::West, .type = normalBotType },
  BotSpec { .pos = GridPos(7, 2), .dir = Direction::East, .type = normalBotType },
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
  BotSpec { .pos = GridPos(0, 5), .dir = Direction::South, .type = normalBotType },
  BotSpec { .pos = GridPos(8, 2), .dir = Direction::North, .type = normalBotType },
};

const LevelSpec levels[numLevels] = {
  LevelSpec {
    .name = "can't fail",
    .numTiles = 3,
    .timeLimit = 45,
    .grid = GridSpec { .w = 9, .h = 7, .tiles = tilesCantFail },
    .numBots = 2,
    .bots = botsCantFail,
  },
  LevelSpec {
    .name = "no choice",
    .numTiles = 1,
    .timeLimit = 120,
    .grid = GridSpec { .w = 9, .h = 7, .tiles = tilesNoChoice },
    .numBots = 2,
    .bots = botsNoChoice,
  },
  LevelSpec {
    .name = "spacious",
    .numTiles = 3,
    .timeLimit = 240,
    .grid = GridSpec { .w = 9, .h = 7, .tiles = tilesSpacious },
    .numBots = 2,
    .bots = botsSpacious,
  },
  LevelSpec {
    .name = "detour",
    .numTiles = 3,
    .timeLimit = 240,
    .grid = GridSpec { .w = 9, .h = 7, .tiles = tilesDetour },
    .numBots = 2,
    .bots = botsDetour,
  },
  LevelSpec {
    .name = "death valley",
    .numTiles = 3,
    .timeLimit = 240,
    .grid = GridSpec { .w = 9, .h = 8, .tiles = tilesDeathValley },
    .numBots = 2,
    .bots = botsDeathValley,
  },
  LevelSpec {
    .name = "twist",
    .numTiles = 3,
    .timeLimit = 240,
    .grid = GridSpec { .w = 9, .h = 8, .tiles = tilesTwist },
    .numBots = 2,
    .bots = botsTwist,
  },
  LevelSpec {
    .name = "cramped",
    .numTiles = 3,
    .timeLimit = 240,
    .grid = GridSpec { .w = 8, .h = 8, .tiles = tilesCramped },
    .numBots = 2,
    .bots = botsCramped,
  },
  LevelSpec {
    .name = "obstructed",
    .numTiles = 3,
    .timeLimit = 240,
    .grid = GridSpec { .w = 9, .h = 8, .tiles = tilesObstructions },
    .numBots = 2,
    .bots = botsObstructions,
  },
  LevelSpec {
    .name = "four of a kind",
    .numTiles = 3,
    .timeLimit = 240,
    .grid = GridSpec { .w = 9, .h = 8, .tiles = tilesFourOfAKind },
    .numBots = 4,
    .bots = botsFourOfAKind,
  },
  LevelSpec {
    .name = "two pair",
    .numTiles = 3,
    .timeLimit = 240,
    .grid = GridSpec { .w = 9, .h = 8, .tiles = tilesTwoPair },
    .numBots = 4,
    .bots = botsTwoPair,
  },
//  LevelSpec {
//    .name = "too hard?",
//    .numTiles = 5,
//    .timeLimit = 360,
//    .grid = GridSpec { .w = 9, .h = 8, .tiles = tilesQueue },
//    .numBots = 4,
//    .bots = botsQueue,
//  },
};

