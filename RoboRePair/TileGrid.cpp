/*
 * Bumble Bots Re-Pair, a Gamebuino game
 *
 * Copyright 2020, Erwin Bonsma
 */

#include "TileGrid.h"
#include "Images.h"

ScreenTile::ScreenTile() : _tile(tiles), _pos(0, 0), _targetPos(0, 0) {}

void ScreenTile::update() {
  _pos.lerp(_targetPos, 32);
}

void ScreenTile::draw() {
  tilesImage.setFrame(_tile->index());
  gb.display.drawImage(_pos.getX(), _pos.getY(), tilesImage);
}

ScreenPos TileGrid::screenPosFor(GridPos pos){
  return ScreenPos(
    _x0 + pos.getX() * _tileSize,
    _y0 + pos.getY() * _tileSize
  );
}

void TileGrid::init(uint8_t width, uint8_t height) {
  _width = width;
  _height = height;
  _maxIndex = _width * _height;
  _tileSize = 13;

  _x0 = 80 - _width * _tileSize / 2;
  _y0 = 64 - _height * _tileSize / 2;

  for (int i = _maxIndex; --i >= 0; ) {
    GridPos pos = indexToPos(i);
    _tiles[i]._targetPos = screenPosFor(pos);
    _tiles[i]._tile = &tiles[0];
    _tiles[i]._pos = ScreenPos(80, 64);
  }
}

void TileGrid::placeTileAt(GridPos pos, const GridTile* tile, bool force) {
  assertTrue(force);

  _tiles[posToIndex(pos)]._tile = tile;
}

void TileGrid::update() {
  ScreenTile* p = _tiles + _maxIndex;
  while (p > _tiles) {
    (--p)->update();
  }
}

void TileGrid::draw() {
  ScreenTile* p = _tiles + _maxIndex;
  while (p > _tiles) {
    (--p)->draw();
  }
}

