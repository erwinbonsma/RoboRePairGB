#include <Gamebuino-Meta.h>

#include "Bot.h"
#include "GridCursor.h"
#include "Images.h"
#include "Levels.h"
#include "Lives.h"
#include "TileTray.h"
#include "Timebar.h"

GridCursor gridCursor;

int8_t musicTrack;
int8_t levelNum;
uint32_t score;

void displayCpuLoad() {
  uint8_t cpuLoad = gb.getCpuLoad();
  gb.display.setColor(cpuLoad < 80 ? INDEX_GREEN : (cpuLoad < 100 ? INDEX_YELLOW : INDEX_RED));
  gb.display.setCursor(1, 1);
  gb.display.printf("%d", cpuLoad);
}

void loadLevel() {
  const LevelSpec& levelSpec = levels[levelNum];
  grid.init(levelSpec.grid);

  destroyAllBots();
  for (int i = 0; i < levelSpec.numBots; ++i) {
    addBot(levelSpec.bots[i]);
  }
  gridCursor.init(GridPos(levelSpec.grid.w / 2, levelSpec.grid.h / 2));

  tileTray.init(levelSpec.numTiles);
  timeBar.init(levelSpec.timeLimit);
}

void nextLevel() {
  ++levelNum;
  if (!lives.inc()) {
    score += 100;
  }

  if (levelNum == numLevels) {
    // TO DO: Celebration!
    levelNum = 0;
  }
  loadLevel();
}

void newGame() {
  levelNum = 0;
  score = 0;
  lives.init();
  loadLevel();

  if (gb.sound.isPlaying(musicTrack)) {
    gb.sound.stop(musicTrack);
  }
  musicTrack = gb.sound.play("bb-track1-intro.wav");
}

void handleDeath() {
  if (lives.dec()) {
    loadLevel();
  } else {
    newGame();
  }
}

void setup() {
  gb.begin();
  newGame();
}

void loop() {
  while(!gb.update());

  grid.update();
  gridCursor.update();
  tileTray.update();
  lives.update();
  if (!timeBar.update()) {
    handleDeath();
  }
  BotStatus status = updateBots();
  if (status != BotStatus::Running) {
    if (status == BotStatus::AllBotsPaired) {
      nextLevel();
    } else {
      handleDeath();
    }
  }

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

  gb.display.printf(" s=%d", (int)status);
}

