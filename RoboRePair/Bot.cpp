/*
 * Bumble Bots Re-Pair, a Gamebuino game
 *
 * Copyright 2020, Erwin Bonsma
 */

#include "Bot.h"

#include "Images.h"
#include "Levels.h"
#include "TileGrid.h"

bool Bot::isBlocked() {
  Bot const* claimedBy = grid.claimTile(_nextPos, this);

  return claimedBy != this;
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

    if (_animClk == 3+2) {
      releasePrevious();
    }

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
  if (tile != nullptr) {
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

    if (_animClk == 2) {
      releasePrevious();
    }

    ++_animClk;
    return false;
  }

  // Blink rear-light by switching between last two sprites
  if (_animClk % 2 == 0) {
    if (rand() % 8 < 5) {
      --_spriteIndex;
      ++_animClk;
    }
  } else {
    if (rand() % 8 < 3) {
      ++_spriteIndex;
      ++_animClk;
    }
  }

  return false;
}

void Bot::handleCrash() {
  _activeImage = &crashedBotsImage;

  if (_dir == Direction::North) {
    _spriteIndex = 0;
    _offset.x = 2;
    _offset.y += 2;
  } else if (_dir == Direction::East) {
    _spriteIndex = 7;
    _offset.x += 2;
    _offset.y = 2;
  }
  //_spriteIndex = (int)_dir * 7;

  _otherAnimFun = &Bot::crashAnim;
  _moveAnimFun = nullptr;
  _animClk = 0;
}

void Bot::init(GridPos pos, Direction dir) {
  _nextPos = pos;
  _nextDir = dir;
  assertTrue(grid.claimTile(pos, this) == this);

  _maxOffset = 6;
  moveStep();

  _activeImage = &botImage;
}

void Bot::destroy() {
  // Note: No harm in releasing tiles that are not owned, as that is a NOOP.
  grid.releaseTile(_prevPos, this);
  grid.releaseTile(_pos, this);
  grid.releaseTile(_nextPos, this);
}

void Bot::update() {
  _clk = (_clk + 1) % _period;
  if (_clk > 0) {
    return;
  }

  if (_moveAnimFun != nullptr && CALL_MEMBER_FN(*this, _moveAnimFun)()) {
    moveStep();
  }
  if (_otherAnimFun != nullptr && CALL_MEMBER_FN(*this, _otherAnimFun)()) {
    _otherAnimFun = nullptr;
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
}

//--------------------------------------------------------------------------------------------------
// Bot globals

Bot botStorage[maxBots];
Bot* bots[maxBots];
Bot** botsBegin = bots;
Bot** botsEnd = bots;

void destroyAllBots() {
  for (auto bot = bots; bot < botsEnd; ++bot) {
    (*bot)->destroy();
  }
  botsEnd = bots;
}

void addBot(const BotSpec& botSpec) {
  int botNum = botsEnd - bots;
  assertTrue(botNum < maxBots);
  botStorage[botNum].init(botSpec.pos, botSpec.dir);
  *botsEnd++ = &botStorage[botNum];
}

