#include <stdio.h>
#include <stdlib.h>
#include "math.h"
#include "brush.h"


typedef struct brush{
    int brushSize;
    COLOR *brushLayout;
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

Brush *createBrush(U_BYTE brushType, int brushSize, COLOR color){
    Brush *br = malloc(sizeof(Brush));
    br->brushSize=brushSize;
    br->brushLayout = malloc(sizeof(COLOR)*brushSize*brushSize);

    generateBrush(br, brushType, color);

    return br;
}

void draw(COLOR *screen, Brush *brush, int x, int y, int screenSizeX, int screenSizeY){

    int offset = (((y-brush->brushSize/2)*screenSizeX)+(x-brush->brushSize/2));

    for(int i = 0; i < brush->brushSize; i++){
        for(int j = 0; j < brush->brushSize; j++){
            if(((i*screenSizeX)+j)+offset > screenSizeX*screenSizeY) continue;
            if(brush->brushLayout[((i*brush->brushSize)+j)] == TRANSPARENT) continue;
            screen[((i*screenSizeX)+j)+offset] = brush->brushLayout[((i*brush->brushSize)+j)];
        }
    }

}


void destroyBrush(Brush *brush){
    free(brush->brushLayout);
    free(brush);
}