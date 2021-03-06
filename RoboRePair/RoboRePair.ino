#include <Gamebuino-Meta.h>

#include "MainMenu.h"
#include "Utils.h"

#ifdef SCREEN_RECORDING
#include "ScreenRecorder.h"
#endif

UpdateFunction updateFunction;
DrawFunction drawFunction;

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
  gb.display.setColor(INDEX_BLACK);
  gb.display.fillRect(0,112,25,12);
  gb.display.setCursor(1,113);
  gb.display.setColor(INDEX_WHITE);
  gb.display.print(cpuLoad);
}

void displayFreeRam() {
  gb.display.setColor(INDEX_BLACK);
  gb.display.fillRect(0,112,25,12);
  gb.display.setCursor(1,113);
  gb.display.setColor(INDEX_WHITE);
  gb.display.print(gb.getFreeRam());
}

void setup() {
  gb.begin();

#ifdef SCREEN_RECORDING
  ScreenRecorder::init(16, true);
#endif
  showMainMenu();
}

void loop() {
  while(!gb.update());

  updateFunction();
  drawFunction();

#ifdef DEVELOPMENT
  #ifdef SCREEN_RECORDING
  ScreenRecorder::monitor(gb.display._buffer);
  #else
  displayCpuLoad();
  //displayFreeRam();
  #endif
#endif
}
