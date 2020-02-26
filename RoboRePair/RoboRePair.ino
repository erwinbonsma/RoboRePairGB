#include <Gamebuino-Meta.h>

#include "Game.h"
#include "HelpMenu.h"
#include "Utils.h"

UpdateFunction updateFunction;
DrawFunction drawFunction;

void displayCpuLoad() {
  uint8_t cpuLoad = gb.getCpuLoad();
  gb.display.setColor(cpuLoad < 80 ? INDEX_GREEN : (cpuLoad < 100 ? INDEX_YELLOW : INDEX_RED));
  gb.display.setCursor(100, 1);
  gb.display.printf("%d", cpuLoad);
}

void setup() {
  gb.begin();

  updateFunction = updateHelp;
  drawFunction = drawHelp;
  //newGame();
}

void loop() {
  while(!gb.update());

  updateFunction();
  drawFunction();

  displayCpuLoad();
}

