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

bool speedUpBots();
void crashAllBots();
void destroyAllBots();
void stopAllBots();
bool allBotsPairing();

// Returns false when no more bots are remaining (and the level should end). This is only signalled once.
bool updateBots();
void drawBots();
void addBot(const BotSpec& botSpec);
bool botAt(GridPos pos);

// Function for carrying out a step in an animation. It return true when the move is done.
typedef bool (Bot::*BotAnimFunction)();

struct BotType {
  bool    small;
  uint8_t look;
  uint8_t period;
};

constexpr uint8_t mediumSpeed = 20;
constexpr uint8_t slowSpeed = 30;
constexpr uint8_t smallFastSpeed = 2;

constexpr uint8_t numBotTypes = 5;
constexpr uint8_t normalBotType = 0;
constexpr uint8_t normalPinkBotType = 1;
constexpr uint8_t slowBlueBotType = 2;
constexpr uint8_t slowBotType = 3;
constexpr uint8_t smallBotType = 4;

class Bot {
  // Movement on grid
  GridPos _pos, _nextPos, _prevPos;
  Direction _dir, _nextDir;

  // The bot that this bot will be meeting given the paths both bots traverse.
  const Bot* _meetingBot;
#ifdef DEVELOPMENT
  int _lastDist; // TMP
#endif

  // The bot that this bot is paired with, if any.
  const Bot* _pairedWithBot;

  bool _destroyed;
  bool _shouldCrash;
  bool _crashed;

  // Main update frequency
  uint8_t _period;
  uint8_t _clk;

  // Fine-grained drawing state
  uint8_t _maxOffset;
  Vector2D _offset;
  int _spriteIndex;
  Image* _activeImage;

  uint8_t _type;

  // Bot animation
  uint8_t _animClk;
  BotAnimFunction _moveAnimFun;
  BotAnimFunction _otherAnimFun;

  // Private function to allow mutual modification of bots
  Bot* mutableBot() const { return const_cast<Bot*>(this); }

  GridPos forcedNextNextPos()  const;
  bool willMeetWith(const Bot* bot) const;
  bool isBlocked();
  void releasePrevious();

  bool moveStraightAnim();
  bool moveReverseAnim();
  bool moveTurnAnim(bool isHard);
  bool moveSmoothTurnAnim();
  bool moveHardTurnAnim();
  void updateMoveAnimFunction();

  void handleMove(const GridTile* tile);
  void moveStep();

  bool crashAnim();
  void handleCrash();

  int pairRotationDelta(int rotation);
  bool pairAnim();
  void paired();

  bool clashAnim();
  void clashed();

  int meetingDistance();
  void handleMeeting();

public:
  GridPos position() const { return _pos; }

  void init(GridPos pos, Direction dir, int type);

  int getType() const { return _type; }

  int getPeriod() const { return _period; }
  void setPeriod(int period) { _period = period; }

  void stop() { _moveAnimFun = nullptr; }
  bool isMoving() const { return _moveAnimFun != nullptr; }
  bool isPairing() const { return _pairedWithBot != nullptr; }

  void destroy();
  bool isDestroyed() const { return _destroyed; }

  void crash(); // Request bot to crash
  bool didCrash() const { return _crashed; }

  void update();
  void draw();
};

