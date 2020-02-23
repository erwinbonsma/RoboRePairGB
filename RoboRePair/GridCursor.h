/*
 * Bumble Bots Re-Pair, a Gamebuino game
 *
 * Copyright 2020, Erwin Bonsma
 */

#include "Utils.h"

class GridCursor {
  GridPos _pos;
  ScreenPos _drawPos;
  ScreenPos _targetDrawPos;
  bool _allowed;

  uint8_t _contractionClk;

  void checkAllowed();
  void positionChanged();

public:
  void init(GridPos pos);

  void update();
  void draw();
};

