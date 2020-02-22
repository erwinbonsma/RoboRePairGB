/*
 * Bumble Bots Re-Pair, a Gamebuino game
 *
 * Copyright 2020, Erwin Bonsma
 */

#include "TileGrid.h"
#include "Images.h"
#include "Levels.h"

TileGrid grid;

void ScreenTile::init(ScreenPos pos) {
  _pos = pos;
  _targetPos = pos;
  _tile = nullptr;
}

void ScreenTile::update() {
  _pos.lerp(_targetPos, 64);
}

void ScreenTile::draw() {
  tilesImage.setFrame(_tile->index());
  gb.display.drawImage(_pos.getX(), _pos.getY(), tilesImage);
}

void TileGrid::init(uint8_t width, uint8_t height) {
  _width = width;
  _height = height;
  _maxIndex = _width * _height;
  _tilesEnd = _tiles + _maxIndex;
  _tileSize = 13;

  _x0 = 80 - _width * _tileSize / 2;
  _y0 = 64 - _height * _tileSize / 2;

  for (int i = _maxIndex; --i >= 0; ) {
    GridPos pos = indexToPos(i);
    _tiles[i].init(ScreenPos(80, 64));
    _tiles[i].setTargetPosition(targetScreenPosOf(pos));
    _tiles[i].setTile(&tiles[0]);
  }
}

void TileGrid::init(const GridSpec& gridSpec) {
  init(gridSpec.w, gridSpec.h);

  const uint8_t* tileIndices = gridSpec.tiles;
  for (int i = _maxIndex; --i >= 0; ) {
    GridPos pos = indexToPos(i);
    placeTileAt(pos, &tiles[tileIndices[i]], true);
  }
}

const ScreenPos TileGrid::targetScreenPosOf(GridPos pos) {
  return ScreenPos(
    _x0 + pos.x * _tileSize,
    _y0 + pos.y * _tileSize
  );
}

const ScreenPos TileGrid::screenPosOf(GridPos pos) {
  return _tiles[posToIndex(pos)].getPosition();
}

const GridTile& TileGrid::tileAt(GridPos pos) {
  return *_tiles[posToIndex(pos)].getTile();
}

void TileGrid::placeTileAt(GridPos pos, const GridTile* tile, bool force) {
  assertTrue(force);

  _tiles[posToIndex(pos)].setTile(tile);
}

Bot const* TileGrid::claimTile(GridPos pos, const Bot* bot) {
  int index = posToIndex(pos);
  const Bot* other = _tiles[index].getBot();
  if (other == nullptr) {
    _tiles[index].setBot(bot);
    return bot;
  } else {
    return other;
  }
}

void TileGrid::releaseTile(GridPos pos, const Bot* bot) {
  int index = posToIndex(pos);
  Bot const* claimer = _tiles[index].getBot();
  if (claimer == bot) {
    _tiles[index].setBot(nullptr);
  }
}

void TileGrid::update() {
  GridScreenTile* p = _tiles;
  while (p < _tilesEnd) {
    (p++)->update();
  }
}

void TileGrid::draw() {
  GridScreenTile* p = _tiles;
  while (p < _tilesEnd) {
    (p++)->draw();
  }
}

