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

void loadLevel();
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

const Gamebuino_Meta::Sound_FX levelDoneSfx[] = {
  {Gamebuino_Meta::Sound_FX_Wave::SQUARE,1,128,0,0,67,14},
  {Gamebuino_Meta::Sound_FX_Wave::SQUARE,1,128,0,0,63,14},
  {Gamebuino_Meta::Sound_FX_Wave::SQUARE,1,131,2,0,56,7},
  {Gamebuino_Meta::Sound_FX_Wave::SQUARE,1,128,0,0,63,7},
  {Gamebuino_Meta::Sound_FX_Wave::SQUARE,0,128,-1,0,56,14},
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
    loadLevel();
    return true;
  }

  return false;
}

bool gameOverAnim() {
  ++animClk;

  if (animClk == 30) {
    gb.sound.fx(diedSfx);
  }

  if (animClk == 90) {
    gb.sound.fx(gameOverSfx);
  }

  if (animClk == 180) {
    showMainMenu();
    return true;
  }

  return false;
}

bool levelDoneAnim() {
  if (drawScore < score) {
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
    if (!lives.inc()) {
      score += 100;
    } else {
      gb.sound.fx(liveBonusSfx);
    }
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

  ++levelNum;
  if (levelNum == numLevels) {
    // TO DO: Celebration!
    levelNum = 0;
  }
  loadLevel();

  return true;
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

  gb.display.clear(INDEX_DARKGRAY);

  lives.init();
  loadLevel();

  updateFunction = updateGame;
  drawFunction = drawGame;
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
    }

    if (!timeBar.update()) {
      gb.sound.fx(timedOutSfx);
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

