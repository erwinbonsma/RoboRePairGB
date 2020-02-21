/*
 * Bumble Bots Re-Pair, a Gamebuino game
 *
 * Copyright 2020, Erwin Bonsma
 */

#include "Bot.h"

#include "Images.h"
#include "TileGrid.h"

void Bot::init(GridPos pos, Direction dir) {
  _nextPos = pos;
  _nextDir = dir;
  assertTrue(grid.claimTile(pos, this) == this);

  moveStep();
}

void Bot::handleMove(const GridTile& tile) {
  _nextDir = tile.randomExitFrom(opposite(_dir));
  _nextPos.x += dx[(int)_nextDir];
  _nextPos.y += dy[(int)_nextDir];
}

void Bot::moveStep() {
  _pos = _nextPos;
  _dir = _nextDir;

  const GridTile& tile = grid.tileAt(_pos);
  handleMove(tile);
}

void Bot::update() {
  _clk = (_clk + 1) % _period;
  if (_clk > 0) {
    return;
  }

  moveStep();
}

void Bot::draw() {
  const ScreenPos screenPos = grid.screenPosOf(_pos);

  int spriteIndex = (int)_dir * 4;
  botImage.setFrame(spriteIndex);

  gb.display.drawImage(screenPos.getX(), screenPos.getY(), botImage);

  gb.display.setColor(WHITE);
  gb.display.setCursorX(64);
  gb.display.setCursorY(0);
  gb.display.printf("(%d,%d) - %d", _pos.x, _pos.y, (int)_dir);
}

