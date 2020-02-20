#include <Gamebuino-Meta.h>

#include "Images.h"
#include "TileGrid.h"

const int w = 12;
const int h = 8;

bool data[w][h];
TileGrid grid;

bool dataAt(int x, int y) {
  if (x < 0 || x >= w || y < 0 || y >= h) {
    return false;
  } else {
    return data[x][y];
  }
}

const GridTile* tileAt(int x, int y) {
  int idx = (dataAt(x,y)
    ? dataAt(x, y-1) + 2*dataAt(x+1, y) + 4*dataAt(x, y+1) + 8*dataAt(x-1, y)
    : 0
  );

  return &tiles[idx];
}

void initGrid() {
  for (int x = 0; x < w; x++) {
    for (int y = 0; y < h; y++) {
      data[x][y] = (rand() % 3) != 0;
    }
  }

  grid.init(w, h);
  for (int i = grid.maxIndex(); --i >= 0; ) {
    GridPos pos = grid.indexToPos(i);
    grid.placeTileAt(pos, tileAt(pos.getX(), pos.getY()), true);
  }
}

void setup() {
  gb.begin();
  initGrid();
}

void loop() {
  while(!gb.update());

  grid.update();

  if (gb.buttons.held(BUTTON_A, 0)) {
    initGrid();
  }

  gb.display.clear();
  grid.draw();
}

