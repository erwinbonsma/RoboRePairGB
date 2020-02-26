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
#include "Palettes.h"
#include "TileTray.h"
#include "Timebar.h"

typedef bool (*AnimFunction)();

int8_t musicTrack;
int8_t levelNum;
uint32_t score;
uint32_t drawScore;

int animClk;
AnimFunction endGameAnimFun;
AnimFunction speedUpAnimFun;

GridCursor gridCursor;

void loadLevel();
void handleLevelDone();
void handleDeath();

// This seems much slower than a full screen clear. Why?
void fastGameScreenClear() {
  memset(gb.display._buffer, 0, 160 * 16 / 2);
}

bool speedUpBotsAnim() {
  if (animClk++ % 6 == 0) {
   return !speedUpBots();
  }

  return false;
}

bool retryAnim() {
  ++animClk;
  // TODO: SFX

  if (animClk == 50) {
    loadLevel();
    return true;
  }

  return false;
}

bool gameOverAnim() {
  ++animClk;
  // TODO: SFX

  if (animClk == 50) {
    newGame();
    return true;
  }

  return false;
}

bool levelDoneAnim() {
  if (drawScore < score) {
    return false;
  }

  ++animClk;
  if (animClk < 30) {
    // Wait
    return false;
  }

  if (animClk == 30) {
    if (!lives.inc()) {
      score += 100;
    }
    return false;
  }

  if (animClk < 60) {
    // Wait
    return false;
  }

  if (timeBar.scoreTicks()) {
    // TODO: SFX
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
}

void setSpeedUpAnimFunction() {
  speedUpAnimFun = speedUpBotsAnim;
  animClk = 0;
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

void newGame() {
  levelNum = 0;
  score = 0;
  endGameAnimFun = nullptr;
  speedUpAnimFun = nullptr;

  lives.init();
  loadLevel();

  if (gb.sound.isPlaying(musicTrack)) {
    gb.sound.stop(musicTrack);
  }
  musicTrack = gb.sound.play("bb-track1-intro.wav");
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

    gridCursor.update();
    tileTray.update();

    if (!timeBar.update()) {
      handleDeath();
    }
  }

  if (drawScore < score) {
    drawScore++;
  }

  if (!gb.sound.isPlaying(musicTrack)) {
    musicTrack = gb.sound.play("bb-track1-loop.wav", true);
  }
}


void drawGame() {
  gb.display.clear(INDEX_DARKGRAY);
  //fastGameScreenClear();

  lives.draw();
  timeBar.draw();
  grid.draw();
  drawBots();
  if (endGameAnimFun == nullptr) {
    tileTray.draw();
    gridCursor.draw();
  }

  gb.display.setColor(INDEX_BROWN);
  gb.display.setCursor(1,1);
  gb.display.print(drawScore);
}

