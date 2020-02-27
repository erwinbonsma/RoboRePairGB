#include <Gamebuino-Meta.h>

#include "MainMenu.h"
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

  showMainMenu();
}

void loop() {
  while(!gb.update());

  updateFunction();
  drawFunction();

  displayCpuLoad();
}

