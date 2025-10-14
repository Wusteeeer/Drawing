#ifndef BRUSH_H
#define BRUSH_H

#ifdef _cplusplus
extern "C" {
#endif

#include "c_util.h"
#include "screen.h"

/*@brief Brush type square*/
#define BT_SQUARE (U_BYTE)0b00000000

/*@brief Brush type circle*/
#define BT_CIRCLE (U_BYTE)0b00000001

typedef struct brush Brush;

Brush *createBrush(U_BYTE brushType, int brushSize, COLOR color, U_BYTE zOrder);
void destroyBrush(Brush *brush);

COLOR lerpColor(COLOR c1, COLOR c2, float t);

void draw(Screen *sc, Brush *brush, int x, int y, int screenSizeX, int screenSizeY);
void changeColor(Brush *brush, COLOR newColor);

#ifdef _cplusplus
} //extern "C"
#endif


#endif //BRUSH_H