#include <Gamebuino-Meta.h>

#include "Images.h"

const int w = 12;
const int h = 8;

bool data[w][h];

void initData() {
  for (int x = 0; x < w; x++) {
    for (int y = 0; y < h; y++) {
      data[x][y] = (rand() % 2) == 0;
    }
  }
}

bool dataAt(int x, int y) {
  if (x < 0 || x >= w || y < 0 || y >= h) {
    return false;
  } else {
    return data[x][y];
  }
}

int spriteAt(int x, int y) {
  if (dataAt(x,y)) {
    return dataAt(x, y-1) + 2*dataAt(x+1, y) + 4*dataAt(x, y+1) + 8*dataAt(x-1, y);
  } else {
    return 0;
  }
}

void setup() {
  gb.begin();
  initData();
}

void drawGrid() {  
  int x0 = 80 - w*13/2;
  int y0 = 64 - h*13/2;

  for (int x = 0; x < w; x++) {
    for (int y = 0; y < h; y++) {
      //int si=(x+y)%16;
      int si=spriteAt(x,y);
      tilesImage.setFrame(si);
      gb.display.drawImage(x0 + x*13, y0 + y*13, tilesImage);
    }
  }  
}

void loop() {
  while(!gb.update());
  gb.display.clear();

  drawGrid();
}

