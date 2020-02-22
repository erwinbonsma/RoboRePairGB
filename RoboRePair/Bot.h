/*
 * Bumble Bots Re-Pair, a Gamebuino game
 *
 * Copyright 2020, Erwin Bonsma
 */

#include <Gamebuino-Meta.h>

#include "Utils.h"

class GridTile;
class Bot;
class BotSpec;

// Function for carrying out a move step. It return true when the move is done. The argument is a
// counter for tracking progress.
typedef bool (Bot::*MoveStepFunction)();

// Globals for tracking set of bots
extern Bot** botsBegin;
extern Bot** botsEnd;

void destroyAllBots();
void addBot(const BotSpec& botSpec);

class Bot {
  GridPos _pos, _nextPos, _prevPos;
  Direction _dir, _nextDir;
  uint8_t _period = 4;
  uint8_t _clk;

  uint8_t _maxOffset;
  uint8_t _moveClk;
  Vector2D _offset;
  int _spriteIndex;
  MoveStepFunction _moveFun;

  bool isBlocked();
  void releasePrevious();

  bool moveStraight();
  bool moveReverse();
  bool moveTurn();
  void updateMoveFunction();

  void handleMove(const GridTile& tile);
  void moveStep();

public:
  void update();
  void draw();

  void init(GridPos pos, Direction dir);
  void destroy();
};

