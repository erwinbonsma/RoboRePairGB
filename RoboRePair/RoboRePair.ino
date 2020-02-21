#include <Gamebuino-Meta.h>

#include "Bot.h"
#include "Images.h"
#include "TileGrid.h"

const int w = 12;
const int h = 8;

bool data[w][h];
Bot bot;

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
      data[x][y] = y == 4 || (rand() % 3) != 0;
    }
  }

  grid.init(w, h);
  for (int i = grid.maxIndex(); --i >= 0; ) {
    GridPos pos = grid.indexToPos(i);
    grid.placeTileAt(pos, tileAt(pos.x, pos.y), true);
  }

  bot.init(GridPos { .x = 6, .y = 4 },  Direction::East);
}

void setup() {
  gb.begin();
  initGrid();
}

void loop() {
  while(!gb.update());

  grid.update();
  bot.update();

  if (gb.buttons.held(BUTTON_A, 0)) {
    initGrid();
  }

  gb.display.clear();
  grid.draw();
  bot.draw();
}

