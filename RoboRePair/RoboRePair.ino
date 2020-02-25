#include <Gamebuino-Meta.h>

#include "Bot.h"
#include "GridCursor.h"
#include "Images.h"
#include "Levels.h"
#include "Lives.h"
#include "TileTray.h"
#include "Timebar.h"

const int w = 12;
const int h = 8;

bool data[w][h];
GridCursor gridCursor;

int8_t musicTrack;

void displayCpuLoad() {
  uint8_t cpuLoad = gb.getCpuLoad();
  gb.display.setColor(cpuLoad < 80 ? INDEX_GREEN : (cpuLoad < 100 ? INDEX_YELLOW : INDEX_RED));
  gb.display.setCursor(1, 1);
  gb.display.printf("%d", cpuLoad);
}

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

void initRandomGrid() {
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

  destroyAllBots();
  addBot(BotSpec { .pos = GridPos { .x = 6, .y = 4 }, .dir = Direction::East });
  gridCursor.init(GridPos(w / 2, h / 2));
}

void initGrid(int levelNum) {
  const LevelSpec& levelSpec = levels[levelNum];
  grid.init(levelSpec.grid);

  destroyAllBots();
  for (int i = 0; i < levelSpec.numBots; ++i) {
    addBot(levelSpec.bots[i]);
  }
  gridCursor.init(GridPos(levelSpec.grid.w / 2, levelSpec.grid.h / 2));
}

void setup() {
  gb.begin();
  initGrid(0);
  tileTray.init(3);
  lives.init();
  timeBar.init(30);
  musicTrack = gb.sound.play("bb-track1-intro.wav");
}

void loop() {
  while(!gb.update());

  grid.update();
  gridCursor.update();
  tileTray.update();
  lives.update();
  timeBar.update();
  updateBots();

  if (!gb.sound.isPlaying(musicTrack)) {
    musicTrack = gb.sound.play("bb-track1-loop.wav", true);
  }

  //if (gb.buttons.held(BUTTON_A, 0)) {
  //  initRandomGrid();
  //}

  gb.display.clear();
  tileTray.draw();
  lives.draw();
  timeBar.draw();
  grid.draw();
  drawBots();
  gridCursor.draw();

  displayCpuLoad();
}

