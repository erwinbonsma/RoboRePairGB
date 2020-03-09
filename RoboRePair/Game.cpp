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
#include "Lights.h"
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
constexpr int maxScoreDigits = 6;
char scoreString[maxScoreDigits + 1];

int animClk;
AnimFunction endGameAnimFun;
AnimFunction speedUpAnimFun;

bool inputDisabled;
GridCursor gridCursor;

void fastGameScreenClear();

bool speedUpBotsAnim();
bool retryAnim();
bool endGameAnim();
bool endGameAnimWithLights();
bool gameOverAnim();
bool levelDoneAnim();

void setEndGameAnimFunction(AnimFunction fun);
void setSpeedUpAnimFunction();

void abortGame();
void abortAttempt();

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

const Gamebuino_Meta::Sound_FX scoreIncSfx[] = {
  {Gamebuino_Meta::Sound_FX_Wave::SQUARE,0,128,-32,0,106,1},
};
const Gamebuino_Meta::Sound_FX scoreDecSfx[] = {
  {Gamebuino_Meta::Sound_FX_Wave::SQUARE,0,128,-32,0,212,1},
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
  // Only clear top of screen. No need to clear grid, as it will overwrite itself
  memset(gb.display._buffer, (int)INDEX_DARKGRAY | ((int)INDEX_DARKGRAY << 4), 80 * 15);
  memset(gb.display._buffer + 40 * 15, (int)INDEX_BLACK | ((int)INDEX_BLACK << 4), 80 * 5);
}

void disableInput() {
  inputDisabled = true;
  gridCursor.setDisabled(true);
  gridCursor.setHidden(true);
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
    gb.sound.fx(scoreIncSfx);
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

bool endGameAnimWithLights() {
  drawCelebrationLights();

  return endGameAnim();
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
  if (drawScore != score) {
    gb.sound.fx(drawScore < score ? scoreIncSfx : scoreDecSfx);
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

  // Life (or score) bonus
  if (animClk == 60) {
    lives.inc();
    gb.sound.fx(liveBonusSfx);
    return false;
  }

  if (animClk < 90) {
    // Wait
    return false;
  }

  // Score remaining time
  if (timeBar.scoreTicks()) {
    gb.sound.fx(scoreIncSfx);
    --animClk; // Undo increase
    return false;
  }

  if (animClk < 120) {
    // Wait
    return false;
  }

  // Penalize imperfections
  constexpr int gridScanPeriod = 5;
  if (animClk < (120 + grid.maxIndex() * gridScanPeriod)) {
    if ((animClk - 120) % gridScanPeriod != 0) {
      return false;
    }
    if (animClk == 120) {
      if (grid.isComplete()) {
        // No imperfections. Skip this scoring step
        animClk = 120 + grid.maxIndex() * gridScanPeriod;
        return false;
      } else {
        gridCursor.setHidden(false);
      }
    }
    GridIndex index = (animClk - 120) / gridScanPeriod;
    GridPos pos = grid.indexToPos(index);
    gridCursor.setPos(pos);
    const GridTile* tile = grid.tileAt(pos);
    if (tile != nullptr && grid.patchTileAt(pos) != tile) {
      // Tile was patched so had open ends. Subtract points
      score -= 10;
    }
    return false;
  }
  if (animClk == (120 + grid.maxIndex() * gridScanPeriod)) {
    gridCursor.setHidden(true);
  }

  if (animClk < (150 + grid.maxIndex() * gridScanPeriod)) {
    // Wait some more
    return false;
  }

  ++levelNum;
  if (levelNum == numLevels) {
    gridMorpher.init(&theEndGridSpec);
    setEndGameAnimFunction(endGameAnimWithLights);
    return false;
  }
  startLevel();

  return true;
}

ScreenPos levelNumberPos;
ScreenPos targetLevelNumberPos;
ScreenPos levelTitlePos;
ScreenPos targetLevelTitlePos;
char levelNumString[3];

void updateLevelStart() {
  levelNumberPos.lerp(targetLevelNumberPos, 48);
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

  gb.display.setColor(INDEX_ORANGE);
  drawText(levelNumberPos.getX(), levelNumberPos.getY(), "level");
  drawText(levelNumberPos.getX() + 40, levelNumberPos.getY(), levelNumString);
  drawText(levelTitlePos.getX(), levelTitlePos.getY(), levels[levelNum].name);

  if (animClk >= 30) {
    gb.display.setColor(INDEX_YELLOW);
    drawText(49, 74, "get ready!");
  }
}

void startLevel() {
  levelNumberPos = ScreenPos(53, 0);
  targetLevelNumberPos = ScreenPos(53, 46);
  int x0 = 80 - textWidth(levels[levelNum].name) / 2;
  levelTitlePos = ScreenPos(x0, 120);
  targetLevelTitlePos = ScreenPos(x0, 60);

  snprintf(levelNumString, 3, "%02d", (levelNum + 1));

  music.stop();
  animClk = 0;

  updateFunction = updateLevelStart;
  drawFunction = drawLevelStart;
}

void setEndGameAnimFunction(AnimFunction fun) {
  endGameAnimFun = fun;
  animClk = 0;
  disableInput();
  timeBar.stop();
  music.stop();
}

void setSpeedUpAnimFunction() {
  speedUpAnimFun = speedUpBotsAnim;
  animClk = 0;
  disableInput();
}

void abortGame() {
  stopAllBots();
  while (lives.dec()) { /* void */ }

  setEndGameAnimFunction(gameOverAnim);
}

void abortAttempt() {
  disableInput();
  speedUpBots();
  crashAllBots();
}

void loadLevel() {
  // Destroy bots before creating new grid, so that they can release all claimed tiles of the old grid
  destroyAllBots();

  const LevelSpec& levelSpec = levels[levelNum];
  grid.init(levelSpec.grid);

  for (int i = 0; i < levelSpec.numBots; ++i) {
    addBot(levelSpec.bots[i]);
  }
  gridCursor.init(GridPos(levelSpec.grid.w / 2, levelSpec.grid.h / 2));

  tileTray.init(levelSpec.numTiles);
  timeBar.init(levelSpec.timeLimit);

  inputDisabled = false;
  music.start();

  gb.display.clear(INDEX_BLACK);

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
  drawScore = 1; // Forces re-generation of drawScoreString
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
    // Act only on first crash (or clash)
    handleDeath();
  }
}

void handleBotClashed() {
  if (endGameAnimFun == nullptr) {
    // Act only on first clash (or crash)
    handleDeath();
  }
}

void incScore(int amount) {
  score += amount;
}

void updateGame() {
  // Clear lights here so that animations can also draw lights.
  clearLights();

  grid.update();
  lives.update();
  if (!updateBots()) {
    handleLevelDone();
  }

  // Also update when user input is disabled as the cursor is also used when scoring the level.
  gridCursor.update();

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
      tileTray.update();
    }

#ifndef SCREEN_RECORDING
    // Ignore while recording is enabled, as both are triggered via the same button
    if (gb.buttons.held(BUTTON_MENU, fps)) {
      abortGame();
      setEndGameAnimFunction(gameOverAnim);
    }
    if (gb.buttons.released(BUTTON_MENU)) {
      // Suicide. Can be useful when pairing is impossible.
      abortAttempt();
    }
#endif
  }

  if (!timeBar.update()) {
    if (allBotsPairing()) {
      // Ignore
      timeBar.stop(true);
    } else {
      // Timed out!
      gb.sound.fx(timedOutSfx);
      stopAllBots();
      handleDeath();
    }
  }

  if (drawScore != score) {
    drawScore += sgn(score - drawScore);
    snprintf(scoreString, maxScoreDigits + 1, "%lu", drawScore);
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
  }
  gridCursor.draw();

  gb.display.setColor(INDEX_BROWN);
  drawText(2, 1, scoreString, 2);
}
