#include <Gamebuino-Meta.h>

#include "MainMenu.h"
#include "Utils.h"

void updateTest() {}

void drawTest() {
  gb.display.clear();
  gb.display.setColor(INDEX_WHITE);
  for (int i = 0; i < 9; i++) {
    drawText(0, i * 14, "the very quick brown fox");
    //drawTextUsingGlyphs(0, i * 14, "the very quick brown fox");
  }
}

UpdateFunction updateFunction = updateTest;
DrawFunction drawFunction = drawTest;

void displayCpuLoad() {
  int cpuLoad = gb.getCpuLoad();
  if (cpuLoad >= 70) {
    gb.display.setColor(INDEX_GREEN);
    gb.display.drawLine(0, 127, min(9, cpuLoad - 70), 127);
  }
  if (cpuLoad >= 80) {
    gb.display.setColor(INDEX_YELLOW);
    gb.display.drawLine(10, 127, 10 + min(20, cpuLoad - 80), 127);
  }
  if (cpuLoad >= 100) {
    gb.display.setColor(INDEX_RED);
    gb.display.drawLine(30, 127, 30 + min(20, cpuLoad - 100), 127);
  }
  if (cpuLoad < 120) {
    gb.display.setColor(INDEX_BLACK);
    gb.display.drawLine(max(0, cpuLoad - 69), 127, 50, 127);
  }
}

void setup() {
  gb.begin();

  //showMainMenu();
}

void loop() {
  while(!gb.update());

  updateFunction();
  drawFunction();

  displayCpuLoad();
}

