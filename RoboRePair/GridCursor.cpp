/*
 * Bumble Bots Re-Pair, a Gamebuino game
 *
 * Copyright 2020, Erwin Bonsma
 */

#include "GridCursor.h"

#include "TileTray.h"

void GridCursor::checkAllowed() {
  const GridTile* tile = tileTray.selectedTile();
  _allowed = (tile != nullptr && grid.canPlaceTileAt(_pos, tile));
}

void GridCursor::positionChanged() {
  _targetDrawPos = grid.targetScreenPosOf(_pos);

  checkAllowed();
}

void GridCursor::init(GridPos pos) {
  _pos = pos;
  positionChanged();
}

void GridCursor::update() {
  bool posChanged = false;

  if (gb.buttons.held(BUTTON_LEFT, 0)) {
    _pos.x = (_pos.x + grid.width() - 1) % grid.width();
    posChanged = true;
  }
  if (gb.buttons.held(BUTTON_RIGHT, 0)) {
    _pos.x = (_pos.x + 1) % grid.width();
    posChanged = true;
  }
  if (gb.buttons.held(BUTTON_UP, 0)) {
    _pos.y = (_pos.y + grid.height() - 1) % grid.height();
    posChanged = true;
  }
  if (gb.buttons.held(BUTTON_DOWN, 0)) {
    _pos.y = (_pos.y + 1) % grid.height();
    posChanged = true;
  }
  if (posChanged) {
    positionChanged();
  }

  if (gb.buttons.held(BUTTON_A, 0)) {
    // TODO: Check there's no bot either
    if (_allowed) {
      tileTray.placeSelectedTileAt(_pos);
      _allowed = false;
    } else {
      // TODO: No Can Do SFX
    }
  }

  if (gb.buttons.held(BUTTON_B, 0)) {
    if (tileTray.numAvailableTiles() >= 2) {
      tileTray.switchTiles();
      checkAllowed();
    } else {
      // TODO: No Can Do SFX
    }
  }

  _drawPos.lerp(_targetDrawPos, 128);
}

void GridCursor::draw() {
  gb.display.setColor(_allowed ? GREEN : RED);
  gb.display.drawRect(_drawPos.getX(), _drawPos.getY(), 13, 13);
}

