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
#include "TileTray.h"
#include "Timebar.h"

typedef bool (*AnimFunction)();

int8_t musicTrack;
int8_t levelNum;
uint32_t score;

int animClk;
AnimFunction gameAnimFun;

GridCursor gridCursor;

void loadLevel();
void nextLevel();
void handleDeath();

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

void setAnimFunction(AnimFunction fun) {
  gameAnimFun = fun;
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

void nextLevel() {
  ++levelNum;
  if (!lives.inc()) {
    score += 100;
  }

  if (levelNum == numLevels) {
    // TO DO: Celebration!
    levelNum = 0;
  }
  loadLevel();
}

void handleDeath() {
  if (lives.dec()) {
    setAnimFunction(retryAnim);
  } else {
    setAnimFunction(gameOverAnim);
  }
}

void newGame() {
  levelNum = 0;
  score = 0;
  gameAnimFun = nullptr;

  lives.init();
  loadLevel();

  if (gb.sound.isPlaying(musicTrack)) {
    gb.sound.stop(musicTrack);
  }
  musicTrack = gb.sound.play("bb-track1-intro.wav");
}

void signalGridComplete() {
  setAnimFunction(speedUpBotsAnim);
}

void signalBotCrashed() {
  handleDeath();
}

void updateGame() {
  grid.update();
  gridCursor.update();
  tileTray.update();
  lives.update();
  if (!timeBar.update()) {
    handleDeath();
  }
  if (!updateBots()) {
    nextLevel();
  }
  if (gameAnimFun != nullptr) {
    if (gameAnimFun()) {
      gameAnimFun = nullptr;
    }
  }

  if (!gb.sound.isPlaying(musicTrack)) {
    musicTrack = gb.sound.play("bb-track1-loop.wav", true);
  }
}


void drawGame() {
  gb.display.clear();
  tileTray.draw();
  lives.draw();
  timeBar.draw();
  grid.draw();
  drawBots();
  gridCursor.draw();
}

