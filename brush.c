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

void changeColor(Brush *brush, COLOR newColor){
    for(int i = 0; i < brush->brushSize; i++){
        for(int j = 0; j < brush->brushSize; j++){
            int index = (i*brush->brushSize)+j;
            if(brush->brushLayout[index] == TRANSPARENT) continue;
            brush->brushLayout[index] = newColor;
        }
    }
}



//TODO: Handle transparency and then allow for exporting image as bitmap
void draw(COLOR *screen, Brush *brush, int x, int y, int screenSizeX, int screenSizeY){

    int offset = (((y-brush->brushSize/2)*screenSizeX)+(x-brush->brushSize/2));
    

    for(int i = 0; i < brush->brushSize; i++){
        for(int j = 0; j < brush->brushSize; j++){
            if(((i*screenSizeX)+j)+offset > screenSizeX*screenSizeY) continue;
            if(brush->brushLayout[((i*brush->brushSize)+j)] == TRANSPARENT) continue;

            COLOR brushColor = ARGBTORGBA(brush->brushLayout[((i*brush->brushSize)+j)]);
            COLOR screenColor = ARGBTORGBA(screen[((i*screenSizeX)+j)+offset]); 

            // int alpha1 = (brushColor&0x000000FF);
            // int alpha2 = (screenColor&0x000000FF);
    
            // float newAlpha = alpha1 + alpha2*(1-alpha1);
            // COLOR newColor = (COLOR)(brushColor*alpha1+screenColor*alpha2*(1-alpha1)/newAlpha);
            
            //TODO: Interpolate from screen color to brush color based on alpha channel
            printf("%d, %d, %d, %d\n", REDCHANNEL(brushColor), GREENCHANNEL(brushColor), BLUECHANNEL(brushColor), ALPHACHANNEL(brushColor));
            printf("%d, %d, %d, %d\n", REDCHANNEL(screenColor), GREENCHANNEL(screenColor), BLUECHANNEL(screenColor), ALPHACHANNEL(screenColor));
            printf("\n");

            screen[((i*screenSizeX)+j)+offset] = RGBATOARGB(brushColor);
        }
    }

}


void destroyBrush(Brush *brush){
    free(brush->brushLayout);
    free(brush);
}