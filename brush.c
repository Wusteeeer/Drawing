#include <stdio.h>
#include <stdlib.h>
#include "math.h"
#include "brush.h"



typedef struct brush{
    int brushSize;
    COLOR *brushLayout;
    U_BYTE zOrder;
}Brush;

static void generateBrush(Brush *br, U_BYTE brushType, COLOR color){
    
    switch(brushType){
        case BT_SQUARE:
            for(int i = 0; i < br->brushSize; i++){
                for(int j = 0; j < br->brushSize; j++){
                    br->brushLayout[i*br->brushSize+j] = color;
                }
            }
        break;
        case BT_CIRCLE:
            for(int i = 0; i < br->brushSize; i++){
                for(int j = 0; j < br->brushSize; j++){

                    if(sqrt((i-br->brushSize/2)*(i-br->brushSize/2)+(j-br->brushSize/2)*(j-br->brushSize/2)) <= (br->brushSize/3)){
                        br->brushLayout[i*br->brushSize+j] = color;
                    }else{
                        br->brushLayout[i*br->brushSize+j] = TRANSPARENT;
                    }
                }
            }

        break;
    }

}

Brush *createBrush(U_BYTE brushType, int brushSize, COLOR color, U_BYTE zOrder){
    Brush *br = malloc(sizeof(Brush));
    br->brushSize=brushSize;
    br->brushLayout = malloc(sizeof(COLOR)*brushSize*brushSize);
    br->zOrder = zOrder;

    generateBrush(br, brushType, color);

    return br;
}

void changeColor(Brush *brush, COLOR newColor){
    for(int i = 0; i < brush->brushSize; i++){
        for(int j = 0; j < brush->brushSize; j++){
            int index = (i*brush->brushSize)+j;
            if(brush->brushLayout[index] == TRANSPARENT) continue;
            brush->brushLayout[index] = newColor;
        }
    }
}


static float lerp(float v0, float v1, float t) {
  return (1 - t) * v0 + t * v1;
}

static float map(long x, long in_min, long in_max, long out_min, long out_max)
{
  return (float)((x - in_min) * (out_max - out_min)) / (float)((in_max - in_min) + out_min);
}

COLOR lerpColor(COLOR c1, COLOR c2, float a){
    float newRed = lerp((float)REDCHANNEL(c1), (float)REDCHANNEL(c2), a);
    float newGreen = lerp((float)GREENCHANNEL(c1), (float)GREENCHANNEL(c2), a);
    float newBlue = lerp((float)BLUECHANNEL(c1), (float)BLUECHANNEL(c2), a);
    return ((int)newBlue)|((int)newGreen<<8)|((int)newRed<<16)|((int)map(a, 0, 1, 0, 255)<<24);
}

void draw(Screen *sc, Brush *brush, int x, int y, int screenSizeX, int screenSizeY){
    
    for(int i = 0; i < brush->brushSize; i++){
        for(int j = 0; j < brush->brushSize; j++){
            int scX = (x-brush->brushSize/2)+j;
            int scY = (y-brush->brushSize/2)+i;
            if(scX >= screenSizeX || scY >= screenSizeY) continue;
            if(brush->brushLayout[((i*brush->brushSize)+j)] == TRANSPARENT) continue;
            if(getPixelZOrder(sc, scX, scY) > brush->zOrder) continue;
 
            COLOR brushColor = brush->brushLayout[((i*brush->brushSize)+j)];
            COLOR screenColor = getPixelColor(sc, scX, scY); 

            int alpha = ALPHACHANNEL(brushColor);            
            float mappedAlpha = map(alpha, 0, 255, 0, 1);
            
            setPixelColor(sc, scX, scY, alpha != 255 ? lerpColor(screenColor, brushColor, mappedAlpha) : brushColor);
        }
    }

}


void destroyBrush(Brush *brush){
    free(brush->brushLayout);
    free(brush);
}