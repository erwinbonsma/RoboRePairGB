/*
 * Bumble Bots Re-Pair, a Gamebuino game
 *
 * Copyright 2020, Erwin Bonsma
 */

#include "Utils.h"

class ProgressTracker {
  bool _improvedHiScore;

  // Updated at the end of each level so that it can be used to determine the
  // level score.
  Score _score;

  void dump();

  void clearStoredHiScore();
  void clearStoredLevelScores();

  void updateHiScore();

public:
  void init();

  Score score() { return _score; }

  Score levelHiScore(int levelIndex);
  Score hiScore();
  bool improvedHiScore() { return _improvedHiScore; }

  void startGame();

  void startLevel(Score totalScore);

  /* Invoke to signal that a level has been completed. This will update stored
   * progress if needed.
   *
   * Returns true iff this is a new level hi.
   */
  bool levelDone(int levelIndex, Score totalScore);

  /* Invoke to signal that the game is done. This will update stored progress
   * if needed.
   *
   * Returns true iff this is a new hi-score
   */
  bool gameDone(uint16_t finalScore);
};

extern ProgressTracker progressTracker;
