/*
 * Bumble Bots Re-Pair, a Gamebuino game
 *
 * Copyright 2020, Erwin Bonsma
 */

#include "Bot.h"

#include "Game.h"
#include "Images.h"
#include "Levels.h"
#include "TileGrid.h"

const Gamebuino_Meta::Sound_FX crashSfx[] = {
  {Gamebuino_Meta::Sound_FX_Wave::NOISE,0,255,-10,0,128,10},
};

const Gamebuino_Meta::Sound_FX fallSfx[] = {
  {Gamebuino_Meta::Sound_FX_Wave::SQUARE,0,128,-1,127,212,40},
};

const Gamebuino_Meta::Sound_FX wiggle1Sfx[] = {
  {Gamebuino_Meta::Sound_FX_Wave::SQUARE,0,64,-1,0,56,2},
};

const Gamebuino_Meta::Sound_FX wiggle2Sfx[] = {
  {Gamebuino_Meta::Sound_FX_Wave::SQUARE,0,64,-1,0,42,2},
};

GridPos Bot::forcedNextNextPos() const {
  const GridTile* tile = grid.tileAt(_nextPos);
  if (tile == nullptr) {
    return GRIDPOS_NONE;
  }

  Direction exitFrom = tile->exitFrom(opposite(_nextDir));
  if (exitFrom == Direction::Multiple) {
    return GRIDPOS_NONE;
  }

  GridPos pos = GridPos(_nextPos);
  pos.add(dirVectors[(int)exitFrom]);
  return pos;
}

bool Bot::willMeetWith(const Bot* bot) const {
  if (bot->_nextPos == _pos) {
    // The bots will meet
    return true;
  }

  if (bot->_nextPos != _nextPos) {
    // The bots will not meet
    return false;
  }

  // Both bots will visit the same tile but may still avoid collision, for example when they
  // approach a crossing for orthogonal directions. Look further ahead.
  return (
    bot->forcedNextNextPos() == _pos &&
    forcedNextNextPos() == bot->_pos
  );
}

bool Bot::isBlocked() {
  if (_meetingBot != nullptr) {
    // Never blocked when meeting another bot
    return false;
  }

  Bot const* claimedBy = grid.claimTile(_nextPos, this);
  if (claimedBy == this) {
    //  Managed to claim the tile
    return false;
  }

  if (willMeetWith(claimedBy)) {
    // Detected a new meeting
    _meetingBot = claimedBy;
    claimedBy->mutableBot()->_meetingBot = this;

    // TMP: Check that meeting bots always move closer
    int dist = meetingDistance();
    claimedBy->mutableBot()->_lastDist = dist;
    _lastDist = dist;

    return false;
  }

  // The tile is blocked by another bot but our paths will not necessarily cross, so just wait
  return true;
}

void Bot::releasePrevious() {
  grid.releaseTile(_prevPos, this);
}

bool Bot::moveStraightAnim() {
  if (_animClk < 12) {
    if (_animClk == 8 && isBlocked()) {
      return false;
    }

    Vector2D dirv = dirVectors[(int)_dir];
    _offset.x += dirv.x;
    _offset.y += dirv.y;

    if (_animClk == 3) {
      releasePrevious();
    }

    ++_animClk;
    return false;
  }

  return true;
}

bool Bot::moveReverseAnim() {
  // Move halfway
  if (_animClk < 6) {
    Vector2D dirv = dirVectors[(int)_dir];
    _offset.x += dirv.x;
    _offset.y += dirv.y;

    if (_animClk == 3) {
      releasePrevious();
    }

    ++_animClk;
    return false;
  }

  // Turn
  if (_animClk < 6+8) {
    _spriteIndex = (_spriteIndex + 1) % 16;

    ++_animClk;
    return false;
  }

  // Return
  if (_animClk < 6+8+6) {
     if (_animClk == 6+8+3 && isBlocked()) {
      return false;
    }

    Vector2D dirv = dirVectors[(int)_dir];
    _offset.x -= dirv.x;
    _offset.y -= dirv.y;

    ++_animClk;
    return false;
  }

  return true;
}

bool Bot::moveTurnAnim() {
  // Initial straight bit
  if (_animClk < 3) {
    Vector2D dirv = dirVectors[(int)_dir];
    _offset.x += dirv.x;
    _offset.y += dirv.y;

    _animClk++;
    return false;
  }

  // Move diagonally and turn
  if (_animClk < 3+4) {
    if (_animClk == 3+1) {
      releasePrevious();

      if (isBlocked()) {
        return false;
      }
    }

    Vector2D dirv1 = dirVectors[(int)_dir];
    Vector2D dirv2 = dirVectors[(int)_nextDir];
    int rotDir = orientation(dirv2, dirv1);

    if (_animClk < 3+3) {
      _offset.x += dirv1.x + dirv2.x;
      _offset.y += dirv1.y + dirv2.y;
    } else {
      _offset.x += dirv2.x;
      _offset.y += dirv2.y;
    }
    _spriteIndex = (_spriteIndex + rotDir + 16) % 16;

    ++_animClk;
    return false;
  }

  // Final straight bit
  if (_animClk < 3+4+2) {
    Vector2D dirv = dirVectors[(int)_nextDir];
    _offset.x += dirv.x;
    _offset.y += dirv.y;

    ++_animClk;
    return false;
  }

  return true;
}

void Bot::updateMoveAnimFunction() {
  if (_dir == _nextDir) {
    _moveAnimFun = &Bot::moveStraightAnim;
  } else if (_dir == opposite(_nextDir)) {
    _moveAnimFun = &Bot::moveReverseAnim;
  } else {
    _moveAnimFun = &Bot::moveTurnAnim;
  }

  _animClk = 0;
}

void Bot::handleMove(const GridTile* tile) {
  _nextDir = tile->randomExitFrom(opposite(_dir));
  Vector2D dirv = dirVectors[(int)_nextDir];
  _nextPos.x += dirv.x;
  _nextPos.y += dirv.y;

  updateMoveAnimFunction();
}

void Bot::moveStep() {
  _prevPos = _pos;
  _pos = _nextPos;
  _dir = _nextDir;

  // Fine-grained drawing state
  Vector2D dirv = dirVectors[(int)opposite(_dir)];
  _offset.x = _maxOffset * dirv.x;
  _offset.y = _maxOffset * dirv.y;
  _spriteIndex = (int)_dir * 4;

  const GridTile* tile = grid.tileAt(_pos);
  if (tile != nullptr && !_shouldCrash) {
    handleMove(tile);
  } else {
    handleCrash();
  }
}

bool Bot::crashAnim() {
  // Falling
  if (_animClk < 5) {
    Vector2D dirv = dirVectors[(int)_dir];
    _offset.x += dirv.x;
    _offset.y += dirv.y;

    ++_spriteIndex;

    if (_animClk == 0) {
      gb.sound.fx(fallSfx);
    }
    if (_animClk == 2) {
      releasePrevious();
    }

    ++_animClk;
    return false;
  }

  // Blink rear-light by switching between last two sprites
  if (_animClk == 5) {
    if (rand() % 8 < 3) {
      ++_spriteIndex;
      _animClk = 6;
    }
  } else {
    if (rand() % 8 < 5) {
      --_spriteIndex;
      _animClk = 5;
    }
  }

  if (!_crashed) {
    _crashed = true;
    handleBotCrashed();
    gb.sound.fx(crashSfx);
  }

  return false;
}

void Bot::handleCrash() {
  stop();

  _activeImage = &crashedBotsImage;

  switch (_dir) {
    case Direction::North:
      _offset.x = 2;
      _offset.y += 2;
      break;
    case Direction::East:
      _offset.x += 1;
      _offset.y = 2;
      break;
    case Direction::South:
      _offset.x = 2;
      _offset.y += 1;
      break;
    case Direction::West:
      _offset.x += 2;
      _offset.y = 2;
      break;
    default:
      assertTrue(false);
  }
  _spriteIndex = (int)_dir * 7;

  _otherAnimFun = &Bot::crashAnim;
  _animClk = 0;
  _period = 6; // Fixed crash speed
}

// Returns the amount that both bots still need to rotate in order to face each other
int Bot::pairRotationDelta(int rotation) {
  return abs(8 - (16 + _pairedWithBot->_spriteIndex - rotation) % 16);
}

bool Bot::pairAnim() {
  // Rotate so that bots face
  while (_animClk == 0 && pairRotationDelta(_spriteIndex) > 0) {
    if (
      pairRotationDelta(_spriteIndex + 1) <
      pairRotationDelta(_spriteIndex - 1)
    ) {
      _spriteIndex = (_spriteIndex + 1) % 16;
    } else {
      _spriteIndex = (_spriteIndex + 15) % 16;
    }
    return false;
  }
  if (_animClk == 0) {
    // Signal loop exit
    ++_animClk;
  }

  if (_animClk == 1) {
    // Synchronize wiggle and pick who initiates sound effects
    bool onlyDone = (_pairedWithBot->_animClk == 0);
    if (onlyDone && this > _pairedWithBot) {
      // Wait a cycle for the other bot to catch up
      return false;
    }

    // Signal successful synchronization
    ++_animClk;
    _period = 4; // Fix speed
    return false;
  }

  // Wiggle
  if (_animClk < 2 + 5*4) {
    switch ((_animClk - 2) % 4) {
      case 0:
        if (this <  _pairedWithBot) {
          gb.sound.fx(wiggle1Sfx);
        }
        // Fall through
      case 3:
        _spriteIndex = (_spriteIndex + 1) % 16;
        break;
      case 2:
        if (this < _pairedWithBot) {
          gb.sound.fx(wiggle2Sfx);
        }
        // Fall through
      case 1:
        _spriteIndex = (_spriteIndex + 15) % 16;
        break;
      default:
        assertTrue(false);
    }

    ++_animClk;
    return false;
  }

  destroy();
  return true;
}

void Bot::paired() {
  stop();

  _pairedWithBot = _meetingBot;
  _meetingBot = nullptr;

  _otherAnimFun = &Bot::pairAnim;
  _animClk = 0;
}

int Bot::meetingDistance() {
  ScreenPos p1 = grid.screenPosOf(_pos);
  p1.add(_offset);

  ScreenPos p2 = grid.screenPosOf(_meetingBot->_pos);
  p2.add(_meetingBot->_offset);

  int dx = p1.getX() - p2.getX();
  int dy = p1.getY() - p2.getY();
  return dx * dx + dy * dy;
}

void Bot::handleMeeting() {
  int dist = meetingDistance();
  if (dist <= 125) {
    _meetingBot->mutableBot()->paired();
    paired();
  } else {
    if (dist > _lastDist) {
      // This should not happen
      stopAllBots();
      _lastDist = -1;
    } else {
      _lastDist = dist;
    }
  }
}

void Bot::init(GridPos pos, Direction dir) {
  _nextPos = pos;
  _nextDir = dir;
  assertTrue(grid.claimTile(pos, this) == this);

  _activeImage = &botImage;
  _meetingBot = nullptr;
  _pairedWithBot = nullptr;
  _otherAnimFun = nullptr;
  _shouldCrash = false;
  _crashed = false;
  _destroyed = false;
  _period = 12; // Default

  _lastDist = 0;

  _maxOffset = 6;
  moveStep();
}

void Bot::destroy() {
  // Note: No harm in releasing tiles that are not owned, as that is a NOOP.
  grid.releaseTile(_prevPos, this);
  grid.releaseTile(_pos, this);
  grid.releaseTile(_nextPos, this);

  _destroyed = true;
}

void Bot::crash() {
  // Do not let bot crash when it is about to meet another bot. Note, when bot is not moving
  // anymore, the request is anyway ignored.
  if (_meetingBot == nullptr) {
    _shouldCrash = true;
  }
}

void Bot::update() {
  _clk = (_clk + 1) % _period;
  if (_clk > 0) {
    return;
  }

  if (_otherAnimFun != nullptr && CALL_MEMBER_FN(*this, _otherAnimFun)()) {
    _otherAnimFun = nullptr;
  }
  if (_moveAnimFun != nullptr && CALL_MEMBER_FN(*this, _moveAnimFun)()) {
    moveStep();
  }

  if (_meetingBot != nullptr) {
    handleMeeting();
  }

  //SerialUSB.printf("moveClk=%d, offset=%d,%d, spriteIndex=%d\n", _animClk, _offset.x, _offset.y, _spriteIndex);
}

void Bot::draw() {
  const ScreenPos screenPos = grid.screenPosOf(_pos);

  _activeImage->setFrame(_spriteIndex);

  gb.display.drawImage(
    screenPos.getX() + _offset.x,
    screenPos.getY() + _offset.y,
    *_activeImage
  );

  if (_lastDist < 0) {
    gb.display.setCursor(20, 1);
    gb.display.setColor(INDEX_RED);
    gb.display.print("!!!");
  }

//  if (_meetingBot != nullptr) {
//    gb.display.setCursor(100, 1);
//    gb.display.setColor(INDEX_WHITE);
//    gb.display.printf("M");
//    if (this < _meetingBot) {
//      gb.display.printf(" d=%d", _dist);
//    }
//  }
}

//--------------------------------------------------------------------------------------------------
// Bot globals

Bot botStorage[maxBots];
Bot* bots[maxBots];
Bot** botsBegin = bots;
Bot** botsEnd = bots;

bool speedUpBots() {
  bool spedUp = false;

  for (auto bot = bots; bot < botsEnd; ++bot) {
    if (!(*bot)->isDestroyed()) {
      if ((*bot)->isMoving() && (*bot)->getPeriod() > 1) {
        (*bot)->setPeriod((*bot)->getPeriod() / 2);
        spedUp = true;
      }
    }
  }

  return spedUp;
}

void crashAllBots() {
  for (auto bot = bots; bot < botsEnd; ++bot) {
    if (!(*bot)->isDestroyed()) {
      (*bot)->crash();
    }
  }
}

void destroyAllBots() {
  for (auto bot = bots; bot < botsEnd; ++bot) {
    if (!(*bot)->isDestroyed()) {
      (*bot)->destroy();
    }
  }
  botsEnd = bots;
}

void stopAllBots() {
  for (auto bot = bots; bot < botsEnd; ++bot) {
    if (!(*bot)->isDestroyed()) {
      (*bot)->stop();
    }
  }
}

bool updateBots() {
  bool botsUpdated = false;
  bool botsRemaining = false;

  for (auto bot = botsBegin; bot < botsEnd; ++bot) {
    if (!(*bot)->isDestroyed()) {
      (*bot)->update();
      botsUpdated = true;
      botsRemaining |= !(*bot)->isDestroyed();
    }
  }

  return botsRemaining==botsUpdated;
}

void drawBots() {
  for (auto bot = botsBegin; bot < botsEnd; ++bot) {
    if (!(*bot)->isDestroyed()) {
      (*bot)->draw();
    }
  }
}

void addBot(const BotSpec& botSpec) {
  int botNum = botsEnd - bots;
  assertTrue(botNum < maxBots);

  Bot& bot = botStorage[botNum];
  bot.init(botSpec.pos, botSpec.dir);
  bot.setPeriod(botSpec.period);

  *botsEnd++ = &bot;
}

bool botAt(GridPos pos) {
  for (auto bot = bots; bot < botsEnd; ++bot) {
    if ((*bot)->position() == pos) {
      return true;
    }
  }

  return false;
}

