#ifndef SCREEN_H
#define SCREEN_H

#include "c_util.h"

typedef struct screen Screen;

Screen *createScreen(int width, int height, COLOR bg, int xOffset, int yOffset);
void destroyScreen(Screen *sc);

void fillScreen(Screen *sc, COLOR color);
COLOR getPixelColor(Screen *sc, int x, int y);
COLOR *getPixels(Screen *sc);
U_BYTE getPixelZOrder(Screen *sc, int x, int y);

void setPixelColor(Screen *sc, int x, int y, COLOR color);
void setPixelZOrder(Screen *sc, int x,  int y, U_BYTE z);

int getScreenWidth(Screen *sc);
int getScreenHeight(Screen *sc);

int getXOffset(Screen *sc);
int getYOffset(Screen *sc);

#endif