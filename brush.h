#ifndef BRUSH_H
#define BRUSH_H

#ifdef _cplusplus
extern "C" {
#endif

/*@brief typedef unsigned byte*/
typedef unsigned char U_BYTE;

/*@brief typedef unsigned long*/
typedef unsigned int COLOR;

/*@brief Brush type square*/
#define BT_SQUARE (U_BYTE)0b00000000

/*@brief Brush type circle*/
#define BT_CIRCLE (U_BYTE)0b00000001

/*@brief Background color*/
#define BACKGROUND (COLOR)0x00202020

/*@brief White color*/
#define WHITE (COLOR)0x00FFFFFF

/*@brief Transparent*/
#define TRANSPARENT (COLOR)-1

typedef struct brush Brush;

Brush *createBrush(U_BYTE brushType, int brushSize, COLOR color);
void destroyBrush(Brush *brush);

void draw(COLOR *screen, Brush *brush, int x, int y, int screenSizeX, int screenSizeY);

#ifdef _cplusplus
} //extern "C"
#endif


#endif //BRUSH_H