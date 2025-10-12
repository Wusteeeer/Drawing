#ifndef BRUSH_H
#define BRUSH_H

#ifdef _cplusplus
extern "C" {
#endif


#define ARGBTORGBA(argb) \
    (((argb&0x000000FF)<<8)|((argb&0x0000FF00)<<8)|((argb&0x00FF0000)<<8)|((argb&0xFF000000)>>24))

#define RGBATOARGB(rgba) \
    (((rgba&0xFF000000)>>8)|((rgba&0x00FF0000)>>8)|((rgba&0x0000FF00)>>8)|((rgba&0x000000FF)<<24))

#define REDCHANNEL(rgba) \
    ((rgba&0xFF000000)>>24)

#define GREENCHANNEL(rgba) \
    ((rgba&0x00FF0000)>>16)

#define BLUECHANNEL(rgba) \
    ((rgba&0x0000FF00)>>8)

#define ALPHACHANNEL(rgba) \
    (rgba&0x000000FF)

/*@brief typedef unsigned byte*/
typedef unsigned char U_BYTE;

/*@brief typedef unsigned long*/
typedef unsigned int COLOR;

/*@brief Brush type square*/
#define BT_SQUARE (U_BYTE)0b00000000

/*@brief Brush type circle*/
#define BT_CIRCLE (U_BYTE)0b00000001

/*@brief Background color*/
#define BACKGROUND (COLOR)0xFF202020

/*@brief White color*/
#define WHITE (COLOR)0xFFFFFFFF

/*@brief Black color*/
#define BLACK (COLOR)0xFF000000

/*@brief Blue color 100% alpha*/
#define BLUE (COLOR)0xFF0000FF

/*@brief Red color 100% alpha*/
#define RED (COLOR)0xFFFF0000

/*@brief Green color 100% alpha*/
#define GREEN (COLOR)0xFF00FF00

/*@brief Yellow color*/
#define YELLOW (COLOR)0xFFFFFF00

/*@brief Transparent*/
#define TRANSPARENT (COLOR)-1

typedef struct brush Brush;

Brush *createBrush(U_BYTE brushType, int brushSize, COLOR color);
void destroyBrush(Brush *brush);

COLOR lerpColor(COLOR c1, COLOR c2, float t);

void draw(COLOR *screen, Brush *brush, int x, int y, int screenSizeX, int screenSizeY);
void changeColor(Brush *brush, COLOR newColor);

#ifdef _cplusplus
} //extern "C"
#endif


#endif //BRUSH_H