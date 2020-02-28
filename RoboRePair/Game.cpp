/*
 * Bumble Bots Re-Pair, a Gamebuino game
 *
 * Copyright 2020, Erwin Bonsma
 */

#include "Game.h"

#include "Bot.h"
#include "GridCursor.h"
#include "Images.h"
#include "Levels.h"
#include "Lives.h"
#include "MainMenu.h"
#include "Music.h"
#include "Palettes.h"
#include "TileTray.h"
#include "Timebar.h"

typedef bool (*AnimFunction)();

int8_t levelNum;
uint32_t score;
uint32_t drawScore;

int animClk;
AnimFunction endGameAnimFun;
AnimFunction speedUpAnimFun;

bool inputDisabled;
GridCursor gridCursor;

void fastGameScreenClear();

bool speedUpBotsAnim();
bool retryAnim();
bool endGameAnim();
bool gameOverAnim();
bool levelDoneAnim();

void setEndGameAnimFunction(AnimFunction fun);
void setSpeedUpAnimFunction();

void loadLevel();
void startLevel();
void handleLevelDone();
void handleDeath();

void updateGame();
void drawGame();

const Gamebuino_Meta::Sound_FX diedSfx[] = {
  {Gamebuino_Meta::Sound_FX_Wave::SQUARE,1,255,0,0,253,10},
  {Gamebuino_Meta::Sound_FX_Wave::NOISE,1,0,0,0,0,2},
  {Gamebuino_Meta::Sound_FX_Wave::SQUARE,1,255,0,0,268,10},
  {Gamebuino_Meta::Sound_FX_Wave::NOISE,1,0,0,0,0,2},
  {Gamebuino_Meta::Sound_FX_Wave::SQUARE,1,255,0,0,300,10},
  {Gamebuino_Meta::Sound_FX_Wave::NOISE,1,0,0,0,0,2},
  {Gamebuino_Meta::Sound_FX_Wave::SQUARE,0,255,-2,0,337,25},
};

const Gamebuino_Meta::Sound_FX gameOverSfx[] = {
  {Gamebuino_Meta::Sound_FX_Wave::SQUARE,1,255,-2,10,253,17},
  {Gamebuino_Meta::Sound_FX_Wave::SQUARE,1,236,-2,10,268,17},
  {Gamebuino_Meta::Sound_FX_Wave::SQUARE,1,216,-2,10,300,17},
  {Gamebuino_Meta::Sound_FX_Wave::SQUARE,0,186,-2,8,337,34},
};

const Gamebuino_Meta::Sound_FX getReadySfx[] = {
  {Gamebuino_Meta::Sound_FX_Wave::SQUARE,1,128,0,0,50,3},
  {Gamebuino_Meta::Sound_FX_Wave::SQUARE,1,4,0,0,100,4},
  {Gamebuino_Meta::Sound_FX_Wave::SQUARE,1,128,0,0,47,6},
  {Gamebuino_Meta::Sound_FX_Wave::SQUARE,0,128,-2,0,50,7},
};

const Gamebuino_Meta::Sound_FX levelDoneSfx[] = {
  {Gamebuino_Meta::Sound_FX_Wave::SQUARE,1,96,0,0,67,14},
  {Gamebuino_Meta::Sound_FX_Wave::SQUARE,1,96,0,0,63,14},
  {Gamebuino_Meta::Sound_FX_Wave::SQUARE,1,98,2,0,56,7},
  {Gamebuino_Meta::Sound_FX_Wave::SQUARE,1,96,0,0,63,7},
  {Gamebuino_Meta::Sound_FX_Wave::SQUARE,0,96,-1,0,56,14},
};

const Gamebuino_Meta::Sound_FX liveBonusSfx[] = {
  {Gamebuino_Meta::Sound_FX_Wave::SQUARE,1,255,0,0,30,1},
  {Gamebuino_Meta::Sound_FX_Wave::SQUARE,1,255,0,0,27,1},
  {Gamebuino_Meta::Sound_FX_Wave::SQUARE,1,255,0,0,30,1},
  {Gamebuino_Meta::Sound_FX_Wave::SQUARE,0,255,0,0,25,1},
};

const Gamebuino_Meta::Sound_FX scoreSfx[] = {
  {Gamebuino_Meta::Sound_FX_Wave::SQUARE,0,128,-32,0,119,1},
};

const Gamebuino_Meta::Sound_FX timedOutSfx[] = {
  {Gamebuino_Meta::Sound_FX_Wave::SQUARE,1,255,-12,-32,106,15},
  //{Gamebuino_Meta::Sound_FX_Wave::NOISE,1,0,0,0,0,1},
  {Gamebuino_Meta::Sound_FX_Wave::SQUARE,1,255,-12,-32,113,15},
  //{Gamebuino_Meta::Sound_FX_Wave::NOISE,1,0,0,0,0,1},
  {Gamebuino_Meta::Sound_FX_Wave::SQUARE,0,255,-6,-32,142,25},
};

const uint8_t gameOverGrid[] = {
   2, 10, 10, 10, 10, 10, 10, 10,  8,
   6,  8,  6, 12,  6, 14, 12,  6,  8,
   5,  4, 20, 22,  5,  5,  5, 20,  8,
   3,  9,  1,  1,  1,  1,  1,  3,  8,
   6, 12,  4,  4,  6,  8, 17, 12,  4,
   5,  5,  5,  5, 20,  8, 20, 13,  1,
   3,  9, 16,  9,  3,  8,  1,  1, 24,
   2, 10, 10, 10, 10, 10, 10, 10,  8,
};
const GridSpec gameOverGridSpec = GridSpec {
  .w = 9, .h = 8, .tiles = gameOverGrid
};

const uint8_t theEndGrid[] = {
   6, 10, 10, 10, 10, 10, 10, 10, 12,
   5,  2, 21,  8,  4,  4,  6,  8,  5,
   5,  0,  5,  0, 20, 22, 20,  8,  5,
   5,  0,  1,  0,  1,  1,  3,  8,  5,
   5,  0,  6,  8, 17, 12, 17, 12,  5,
   5,  0, 20,  8,  5,  5,  5,  5,  5,
   5,  0,  3,  8,  1,  1, 16,  9,  5,
   3, 10, 10, 10, 10, 10, 10, 10,  9,
};
const GridSpec theEndGridSpec = GridSpec {
  .w = 9, .h = 8, .tiles = theEndGrid
};


void fastGameScreenClear() {
  memset(gb.display._buffer, (int)INDEX_DARKGRAY | ((int)INDEX_DARKGRAY << 4), 160 * 20 / 2);
}

bool speedUpBotsAnim() {
  if (animClk++ % 6 == 0) {
   return !speedUpBots();
  }

  return false;
}

bool retryAnim() {
  ++animClk;

  if (animClk == 30) {
    gb.sound.fx(diedSfx);
  }

  if (animClk == 90) {
    startLevel();
    return true;
  }

  return false;
}

bool endGameAnim() {
  if (drawScore < score) {
    gb.sound.fx(scoreSfx);
    return false;
  }

  if (!lives.fullyDrawn()) {
    return false;
  }

  if (!gridMorpher.morphStep()) {
    return false;
  }

  if (animClk < 60) {
    ++animClk;
    return false;
  }
  if (animClk == 60) {
    if (lives.dec()) {
      incScore(100);
    } else {
      ++animClk;
    }
    return false;
  }

  ++animClk;
  if (animClk == 250 || gb.buttons.held(BUTTON_A, 0)) {
    showMainMenu();
    return true;
  }
  return false;
}

bool gameOverAnim() {
  ++animClk;

  if (animClk == 30) {
    gb.sound.fx(diedSfx);
    return false;
  }

  if (animClk == 90) {
    stopAllBots();
    gb.sound.fx(gameOverSfx);
    gridMorpher.init(&gameOverGridSpec);
    setEndGameAnimFunction(endGameAnim);
    return false;
  }

  return false;
}

bool levelDoneAnim() {
  if (drawScore < score) {
    gb.sound.fx(scoreSfx);
    return false;
  }

  if (!lives.fullyDrawn()) {
    return false;
  }

  ++animClk;
  if (animClk == 1) {
    gb.sound.fx(levelDoneSfx);
  }

  if (animClk < 60) {
    // Wait
    return false;
  }

  if (animClk == 60) {
    lives.inc();
    gb.sound.fx(liveBonusSfx);
    return false;
  }

  if (animClk < 90) {
    // Wait
    return false;
  }

  if (timeBar.scoreTicks()) {
    gb.sound.fx(scoreSfx);
    return false;
  }

  if (animClk < 120) {
    // Wait
    return false;
  }

  ++levelNum;
  if (levelNum == numLevels) {
    gridMorpher.init(&theEndGridSpec);
    setEndGameAnimFunction(endGameAnim);
    return false;
  }
  startLevel();

  return true;
}

ScreenPos levelTitlePos;
ScreenPos targetLevelTitlePos;

void updateLevelStart() {
  levelTitlePos.lerp(targetLevelTitlePos, 48);
  ++animClk;

  if (animClk == 30) {
    gb.sound.fx(getReadySfx);
  }

  if (animClk == 60 || gb.buttons.held(BUTTON_A, 0)) {
    loadLevel();
  }
}

void drawLevelStart() {
  gb.display.clear();
  gb.display.setColor(animClk < 30 ? INDEX_ORANGE : INDEX_YELLOW);
  drawText(levelTitlePos.getX(), levelTitlePos.getY(), "get ready!");
}

void startLevel() {
  levelTitlePos = ScreenPos(48, 0);
  targetLevelTitlePos = ScreenPos(48, 60);
  music.stop();
  animClk = 0;

  updateFunction = updateLevelStart;
  drawFunction = drawLevelStart;
}

void setEndGameAnimFunction(AnimFunction fun) {
  endGameAnimFun = fun;
  animClk = 0;
  inputDisabled = true;
  music.stop();
}

void setSpeedUpAnimFunction() {
  speedUpAnimFun = speedUpBotsAnim;
  animClk = 0;
  inputDisabled = true;
}

void loadLevel() {
  const LevelSpec& levelSpec = levels[levelNum];
  grid.init(levelSpec.grid);

  destroyAllBots();
  for (int i = 0; i < levelSpec.numBots; ++i) {
    addBot(levelSpec.bots[i]);
  }
  gridCursor.init(GridPos(levelSpec.grid.w / 2, levelSpec.grid.h / 2));

  tileTray.init(levelSpec.numTiles);
  timeBar.init(levelSpec.timeLimit);

  inputDisabled = false;
  music.start();

  gb.display.clear(INDEX_DARKGRAY);

  updateFunction = updateGame;
  drawFunction = drawGame;
}

void handleLevelDone() {
  setEndGameAnimFunction(levelDoneAnim);
}

void handleDeath() {
  if (lives.dec()) {
    setEndGameAnimFunction(retryAnim);
  } else {
    setEndGameAnimFunction(gameOverAnim);
  }
}

void startGame() {
  levelNum = 0;
  score = 0;
  endGameAnimFun = nullptr;
  speedUpAnimFun = nullptr;

  lives.init();
  startLevel();
}

void handleGridComplete() {
  setSpeedUpAnimFunction();
}

void handleBotCrashed() {
  if (endGameAnimFun == nullptr) {
    // Act only on first crash
    handleDeath();
  }
}

void incScore(int amount) {
  score += amount;
}

void updateGame() {
  grid.update();
  lives.update();
  if (!updateBots()) {
    handleLevelDone();
  }

  if (endGameAnimFun != nullptr) {
    if (endGameAnimFun()) {
      endGameAnimFun = nullptr;
    }
  } else {
    if (speedUpAnimFun != nullptr) {
      if (speedUpAnimFun()) {
        speedUpAnimFun = nullptr;
      }
    }

    if (!inputDisabled) {
      gridCursor.update();
      tileTray.update();

      if (gb.buttons.held(BUTTON_MENU, 0)) {
        // Suicide. Can be useful when pairing is impossible.
        inputDisabled = true;
        speedUpBots();
        crashAllBots();
      }
    }

    if (!timeBar.update()) {
      // Timed out!
      gb.sound.fx(timedOutSfx);
      stopAllBots();
      handleDeath();
    }
  }

  if (drawScore < score) {
    drawScore++;
  }

  music.update();
}


void drawGame() {
  //gb.display.clear(INDEX_DARKGRAY);
  fastGameScreenClear();

  lives.draw();
  timeBar.draw();
  grid.draw();
  drawBots();
  if (!inputDisabled) {
    tileTray.draw();
    gridCursor.draw();
  }

  gb.display.setColor(INDEX_BROWN);
  gb.display.setCursor(1,1);
  gb.display.print(drawScore);
}

