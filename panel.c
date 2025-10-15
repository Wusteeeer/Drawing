#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <math.h>
#include "panel.h"


typedef struct panel{
    int x, y;
    int width, height, cornerRadius;
    bool show;
    U_BYTE zOrder;
    COLOR *panelColor;
    COLOR *coveredColor;
}Panel;

Panel *createPanel(int x, int y, int width, int height, int cornerRadius, U_BYTE zOrder, COLOR color){

    Panel *p = malloc(sizeof(Panel));
    p->x = x;
    p->y = y;
    p->zOrder = zOrder;
    p->width = width;
    p->height = height;
    p->cornerRadius = cornerRadius;
    p->panelColor = malloc(sizeof(COLOR)*width*height);
    p->coveredColor = malloc(sizeof(COLOR)*width*height);
    p->show = true;

    for(int i = 0; i < height; i++){
        for(int j = 0; j < width; j++){
            p->panelColor[(i*width)+j]=color;
        }
    }

    return p;
}
void destroyPanel(Panel *p){
    free(p->panelColor);
    free(p->coveredColor);
    free(p);
}

void drawPanel(Panel *p, Screen *sc){

    for(int i = 0; i < p->height; i++){
        for(int j = 0; j < p->width; j++){
            int x = p->x+j;
            int y = p->y+i;
            if(x >= getScreenWidth(sc)) continue;
            if(y >= getScreenHeight(sc)) continue;
            p->coveredColor[(i*p->width)+j] = getPixelColor(sc, x, y);

            if(x >= p->x+p->width-p->cornerRadius || x <= p->cornerRadius+p->x){
                int xPos = x <= p->cornerRadius+p->x ? (p->cornerRadius+p->x) : (p->x+p->width-p->cornerRadius);
                int yPos = (p->height/2)+p->y;
                                
                float distance = sqrt((float)(x-xPos)*(float)(x-xPos)+(float)(y-yPos)*(float)(y-yPos));
                if(abs(distance) > p->height/2) continue;
       
            }
            
            setPixelColor(sc, x, y, p->panelColor[((i*p->width)+j)]);
            setPixelZOrder(sc, x, y, p->zOrder);

        }
    }

}

void hidePanel(Panel *p, Screen *sc){
    for(int i = 0; i < p->height; i++){
        for(int j = 0; j < p->width; j++){
            int x = p->x+j;
            int y = p->y+i;
            if(x >= getScreenWidth(sc)) continue;
            if(y >= getScreenHeight(sc)) continue;

            setPixelColor(sc, x, y, p->coveredColor[(i*p->width)+j]);
            setPixelZOrder(sc, x, y, 0);

        }
    }
}


void flipPanel(Panel *p, Screen *sc){
    if(p->show){
        drawPanel(p, sc);
    }
    else{
        hidePanel(p, sc);
    }
    p->show = !p->show;
}