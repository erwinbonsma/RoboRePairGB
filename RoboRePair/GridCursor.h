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
  // Can the active tile be placed at the current position?
  bool _allowed;

  // Is user input handled?
  bool _disabled;

  // Is the cursor shown?
  bool _hidden;

  uint8_t _contractionClk;

  void checkAllowed();
  void positionChanged();

public:
  void setDisabled(bool flag) { _disabled = flag; }
  bool isDisabled() { return _disabled; }

  void setHidden(bool flag) { _hidden = flag; }
  bool isHidden() { return _hidden; }

  void setPos(GridPos pos) { _pos = pos; positionChanged(); }
  GridPos getPos() { return _pos; }

  void init(GridPos pos);

  void update();
  void draw();
};

