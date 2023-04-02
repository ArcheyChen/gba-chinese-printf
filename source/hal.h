#pragma once
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <gba.h>
#include "my_font.h"


u16 (*vram)[240] = (u16 (*)[240])VRAM;

inline int halGetScreenWidth() { return 240; }

inline int halGetScreenHeight() { return 160; }

void halDrawPixel(int x, int y, u16 color) { vram[y][x] = color; }

const char *halGetFontDataPtr() {
  return my_font;
}
void halClearPixel(){
  memset(vram,0,sizeof(u16)*240*160);
}