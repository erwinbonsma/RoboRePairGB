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

// Function for carrying out a step in an animation. It return true when the move is done.
typedef bool (Bot::*AnimFunction)();

// Globals for tracking set of bots
extern Bot** botsBegin;
extern Bot** botsEnd;

void destroyAllBots();
void addBot(const BotSpec& botSpec);

class Bot {
  // Movement on grid
  GridPos _pos, _nextPos, _prevPos;
  Direction _dir, _nextDir;

  // Main update frequency
  uint8_t _period = 25; //4;
  uint8_t _clk;

  // Fine-grained drawing state
  uint8_t _maxOffset;
  Vector2D _offset;
  int _spriteIndex;
  Image* _activeImage;

  // Bot animation
  uint8_t _animClk;
  AnimFunction _moveAnimFun;
  AnimFunction _otherAnimFun;

  bool isBlocked();
  void releasePrevious();

  bool moveStraightAnim();
  bool moveReverseAnim();
  bool moveTurnAnim();
  void updateMoveAnimFunction();

  void handleMove(const GridTile* tile);
  void moveStep();

  bool crashAnim();
  void handleCrash();

public:
  void init(GridPos pos, Direction dir);
  void destroy();

  void update();
  void draw();
};

