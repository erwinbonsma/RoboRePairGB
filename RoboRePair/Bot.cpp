/*
 * Bumble Bots Re-Pair, a Gamebuino game
 *
 * Copyright 2020, Erwin Bonsma
 */

#include "Bot.h"

#include "Images.h"
#include "TileGrid.h"

bool Bot::isBlocked() {
  Bot const* claimedBy = grid.claimTile(_nextPos, this);

  return claimedBy != this;
}

void Bot::releasePrevious() {
  grid.releaseTile(_prevPos, this);
}

bool Bot::moveStraight() {
  if (_moveClk < 12) {
    if (_moveClk == 8 && isBlocked()) {
      return false;
    }

    Vector2D dirv = dirVectors[(int)_dir];
    _offset.x += dirv.x;
    _offset.y += dirv.y;

    if (_moveClk == 3) {
      releasePrevious();
    }

    ++_moveClk;
    return false;
  }

  return true;
}

bool Bot::moveReverse() {
  // Move halfway
  if (_moveClk < 6) {
    Vector2D dirv = dirVectors[(int)_dir];
    _offset.x += dirv.x;
    _offset.y += dirv.y;

    if (_moveClk == 3) {
      releasePrevious();
    }

    ++_moveClk;
    return false;
  }

  // Turn
  if (_moveClk < 6+8) {
    _spriteIndex = (_spriteIndex + 1) % 16;

    ++_moveClk;
    return false;
  }

  // Return
  if (_moveClk < 6+8+6) {
     if (_moveClk == 6+8+3 && isBlocked()) {
      return false;
    }

    Vector2D dirv = dirVectors[(int)_dir];
    _offset.x -= dirv.x;
    _offset.y -= dirv.y;

    ++_moveClk;
    return false;
  }

  return true;
}

bool Bot::moveTurn() {
  // Initial straight bit
  if (_moveClk < 3) {
    Vector2D dirv = dirVectors[(int)_dir];
    _offset.x += dirv.x;
    _offset.y += dirv.y;

    _moveClk++;
    return false;
  }

  // Move diagonally and turn
  if (_moveClk < 3+4) {
    if (_moveClk == 3+1) {
      if (isBlocked()) {
        return false;
      }
    }

    Vector2D dirv1 = dirVectors[(int)_dir];
    Vector2D dirv2 = dirVectors[(int)_nextDir];
    int rotDir = orientation(dirv2, dirv1);

    if (_moveClk < 3+3) {
      _offset.x += dirv1.x + dirv2.x;
      _offset.y += dirv1.y + dirv2.y;
    } else {
      _offset.x += dirv2.x;
      _offset.y += dirv2.y;
    }
    _spriteIndex = (_spriteIndex + rotDir + 16) % 16;

    if (_moveClk == 3+2) {
      releasePrevious();
    }

    ++_moveClk;
    return false;
  }

  // Final straight bit
  if (_moveClk < 3+4+2) {
    Vector2D dirv = dirVectors[(int)_nextDir];
    _offset.x += dirv.x;
    _offset.y += dirv.y;

    ++_moveClk;
    return false;
  }

  return true;
}

void Bot::init(GridPos pos, Direction dir) {
  _nextPos = pos;
  _nextDir = dir;
  assertTrue(grid.claimTile(pos, this) == this);

  _maxOffset = 6;

  moveStep();
}

void Bot::updateMoveFunction() {
  if (_dir == _nextDir) {
    _moveFun = &Bot::moveStraight;
  } else if (_dir == opposite(_nextDir)) {
    _moveFun = &Bot::moveReverse;
  } else {
    _moveFun = &Bot::moveTurn;
  }

  _moveClk = 0;
}

void Bot::handleMove(const GridTile& tile) {
  _nextDir = tile.randomExitFrom(opposite(_dir));
  Vector2D dirv = dirVectors[(int)_nextDir];
  _nextPos.x += dirv.x;
  _nextPos.y += dirv.y;

  updateMoveFunction();
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

  const GridTile& tile = grid.tileAt(_pos);
  handleMove(tile);
}

void Bot::update() {
  _clk = (_clk + 1) % _period;
  if (_clk > 0) {
    return;
  }

  if (CALL_MEMBER_FN(*this, _moveFun)()) {
    moveStep();
  }
  //SerialUSB.printf("moveClk=%d, offset=%d,%d, spriteIndex=%d\n", _moveClk, _offset.x, _offset.y, _spriteIndex);
}

void Bot::draw() {
  const ScreenPos screenPos = grid.screenPosOf(_pos);

  botImage.setFrame(_spriteIndex);

  gb.display.drawImage(
    screenPos.getX() + _offset.x,
    screenPos.getY() + _offset.y,
    botImage
  );

  gb.display.setColor(WHITE);
  gb.display.setCursorX(64);
  gb.display.setCursorY(0);
  gb.display.printf("(%d,%d) - %d", _pos.x, _pos.y, (int)_dir);
}

