/*
 * Bumble Bots Re-Pair, a Gamebuino game
 *
 * Copyright 2020, Erwin Bonsma
 */

#include "ProgressTracker.h"

#include "Levels.h"

//-----------------------------------------------------------------------------
// ProgressTracker implementation

constexpr uint8_t VMAJOR = 1;
constexpr uint8_t VMINOR = 0;

constexpr uint8_t SAVEINDEX_VMAJOR = 0;
constexpr uint8_t SAVEINDEX_VMINOR = 1;
constexpr uint8_t SAVEINDEX_HISCORE = 2;
constexpr uint8_t SAVEINDEX_LEVELHI_L0 = 3;
constexpr uint8_t SAVEINDEX_LAST = SAVEINDEX_LEVELHI_L0 + numLevels - 1;

void ProgressTracker::clearStoredHiScore() {
  gb.save.set(SAVEINDEX_HISCORE, (int32_t)0);
}

void ProgressTracker::clearStoredLevelScores() {
  for (uint8_t level = 0; level < numLevels; level++) {
    gb.save.set(SAVEINDEX_LEVELHI_L0 + level, (int32_t)0);
  }
}

void ProgressTracker::init() {
  if (
    gb.save.get(SAVEINDEX_VMAJOR) != VMAJOR ||
    gb.save.get(SAVEINDEX_VMINOR) != VMINOR
  ) {
    // Reset all data. Although format itself has not changed, levels have been
    // tweaked so that previous scores are not valid anymore.
    clearStoredLevelScores();
    clearStoredHiScore();
  }

  dump();

  gb.save.set(SAVEINDEX_VMAJOR, (int32_t)VMAJOR);
  gb.save.set(SAVEINDEX_VMINOR, (int32_t)VMINOR);
}

void ProgressTracker::dump() {
#ifdef DEVELOPMENT
  SerialUSB.printf("Save file format v%d.%d\n", gb.save.get(SAVEINDEX_VMAJOR), gb.save.get(SAVEINDEX_VMINOR));
  SerialUSB.printf("High score = %d\n", gb.save.get(SAVEINDEX_HISCORE));
  for (uint8_t i = 0; i < numLevels; i++) {
    SerialUSB.printf("Max score level %d = %d\n", (i + 1), gb.save.get(SAVEINDEX_LEVELHI_L0 + i));
  }
#endif
}

Score ProgressTracker::levelHiScore(int level) {
  return gb.save.get(SAVEINDEX_LEVELHI_L0 + level);
}

Score ProgressTracker::hiScore() {
  return gb.save.get(SAVEINDEX_HISCORE);
}

void ProgressTracker::startGame() {
  _score = 0;
  _improvedHiScore = false;
}

void ProgressTracker::updateHiScore() {
  Score oldHiScore = hiScore();

  if (_score > oldHiScore) {
    gb.save.set(SAVEINDEX_HISCORE, (int32_t)_score);
    _improvedHiScore = true;
  }
}

void ProgressTracker::startLevel(Score score) {
  _score = score;
}

bool ProgressTracker::levelDone(int level, Score score) {
  Score oldLevelHi = levelHiScore(level);
  Score levelScore = score - _score;
  bool improvedLevelHi = false;

  if (levelScore > oldLevelHi) {
    // New level hi-score!
    gb.save.set(SAVEINDEX_LEVELHI_L0 + level, levelScore);
    improvedLevelHi = true;
  }

  updateHiScore();

  return improvedLevelHi;
}

bool ProgressTracker::gameDone(Score finalScore) {
  _score = finalScore;

  updateHiScore();

  return improvedHiScore();
}

ProgressTracker progressTracker;
