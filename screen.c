#include <stdio.h>
#include <stdlib.h>
#include "screen.h"


typedef struct screen{
    int width;
    int height;
    U_BYTE *zOrders;
    COLOR *pixels;
}Screen;

Screen *createScreen(int width, int height, COLOR bg){
    Screen *sc = malloc(sizeof(Screen));
    sc->pixels = malloc(sizeof(COLOR)*width*height);
    sc->zOrders = malloc(sizeof(U_BYTE)*width*height);
    sc->width = width;
    sc->height = height;
    fillScreen(sc, bg);
    for(int y = 0; y < height; y++){
        for(int x = 0; x < width; x++){
            setPixelZOrder(sc, x, y, 0);
        }
    }
    return sc;
}

void destroyScreen(Screen *sc){
    free(sc->pixels);
    free(sc->zOrders);
    free(sc);
}

void fillScreen(Screen *sc, COLOR color){

    for(int y = 0; y < sc->height; y++){
        for(int x = 0; x < sc->width; x++){
            setPixelColor(sc, x, y, color);
        }
    }
}

COLOR getPixelColor(Screen *sc, int x, int y){
    return sc->pixels[(y*sc->width)+x];
}

COLOR *getPixels(Screen *sc){
    return sc->pixels;
}

U_BYTE getPixelZOrder(Screen *sc, int x, int y){
    return sc->zOrders[(y*sc->width)+x];
}

void setPixelColor(Screen *sc, int x, int y, COLOR color){
    sc->pixels[(y*sc->width)+x] = color;
}

void setPixelZOrder(Screen *sc, int x,  int y, U_BYTE z){
    sc->zOrders[(y*sc->width)+x] = z;
}

int getScreenWidth(Screen *sc){
    return sc->width;
}

int getScreenHeight(Screen *sc){
    return sc->height;
}