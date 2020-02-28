/*
 * Bumble Bots Re-Pair, a Gamebuino game
 *
 * Copyright 2020, Erwin Bonsma
 */

#include "GridCursor.h"

#include "Bot.h"
#include "Game.h"
#include "Images.h"
#include "TileTray.h"

const Gamebuino_Meta::Sound_FX noCanDoSfx[] = {
  {Gamebuino_Meta::Sound_FX_Wave::SQUARE,0,128,0,0,450,3},
};

const Gamebuino_Meta::Sound_FX tilePlacedSfx[] = {
  {Gamebuino_Meta::Sound_FX_Wave::SQUARE,1,133,-24,127,100,1},
  {Gamebuino_Meta::Sound_FX_Wave::SQUARE,0,128,-48,0,71,1},
};

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

  if (_contractionClk > 0) {
    _contractionClk--;
  }

  if (gb.buttons.held(BUTTON_A, 0)) {
    if (_allowed && !botAt(_pos)) {
      tileTray.placeSelectedTileAt(_pos);
      _contractionClk = 20;
      _allowed = false;
      incScore(10);
      gb.sound.fx(tilePlacedSfx);
    } else {
      gb.sound.fx(noCanDoSfx);
   }
  }

  if (gb.buttons.held(BUTTON_B, 0)) {
    if (tileTray.numAvailableTiles() >= 2) {
      tileTray.switchTiles();
      checkAllowed();
    } else {
      gb.sound.fx(noCanDoSfx);
    }
  }

  _drawPos.lerp(_targetDrawPos, 128);
}

void GridCursor::draw() {
  if (_contractionClk > 0) {
    int d = _contractionClk == 0 ? 0 : (10 - abs(_contractionClk - 10)) / 2;
    gb.display.setColor(INDEX_GRAY);
    gb.display.drawRect(_drawPos.getX() + d, _drawPos.getY() + d, 13 - 2*d, 13 - 2*d);
  } else {
    const GridTile* tile = tileTray.selectedTile();
    if (tile != nullptr) {
      tilesPreviewImage.setFrame(tile->index() + numPreviewTiles * _allowed);
      gb.display.drawImage(_drawPos.getX(), _drawPos.getY(), tilesPreviewImage);
    }

    gb.display.setColor(INDEX_GRAY);
    gb.display.drawRect(_drawPos.getX(), _drawPos.getY(), 13, 13);
  }
}

