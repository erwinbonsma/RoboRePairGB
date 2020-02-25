#include <Gamebuino-Meta.h>

#include "Game.h"

void displayCpuLoad() {
  uint8_t cpuLoad = gb.getCpuLoad();
  gb.display.setColor(cpuLoad < 80 ? INDEX_GREEN : (cpuLoad < 100 ? INDEX_YELLOW : INDEX_RED));
  gb.display.setCursor(1, 1);
  gb.display.printf("%d", cpuLoad);
}

void setup() {
  gb.begin();
  newGame();
}

void loop() {
  while(!gb.update());

  updateGame();
  drawGame();
  //displayCpuLoad();
}

