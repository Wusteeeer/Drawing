#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <math.h>
#include "panel.h"
#include "brush.h"


typedef struct panel{
    int x, y;
    int width, height, cornerRadius, shadowLength, shadowXOffset, shadowYOffset;
    bool show, horizontal;
    U_BYTE zOrder;
    COLOR panelColor;
    COLOR *coveredColor;
    COLOR *coveredColorShadow;
}Panel;


Panel *createPanel(int x, int y, int width, int height, int cornerRadius, U_BYTE zOrder, COLOR color, int shadowLength, int shadowXOffset, int shadowYOffset){

    Panel *p = malloc(sizeof(Panel));
    p->x = x;
    p->y = y;
    p->zOrder = zOrder;
    p->width = width;
    p->height = height;
    p->cornerRadius = cornerRadius;
    p->panelColor = color;
    p->coveredColor = malloc(sizeof(COLOR)*width*height);
    p->show = true;
    p->horizontal = width >= height;

    if(shadowLength > 0){
        p->shadowLength = shadowLength;
        p->shadowXOffset = shadowXOffset;
        p->shadowYOffset = shadowYOffset;
        p->coveredColorShadow = malloc(sizeof(COLOR)*width*shadowLength);
    }
    

    return p;
}
void destroyPanel(Panel *p){
    free(p->coveredColor);
    if(p->coveredColorShadow) free(p->coveredColorShadow);
    free(p);
}


//TODO: Make rounding more generalized for any orientation of panel (using vectors)
static bool withinCorner(int x, int y, int px, int py, int width, int height, int cornerRadius){
    

    if(x >= px+width-cornerRadius || x <= cornerRadius+px){
        int xPos = x <= cornerRadius+px ? (cornerRadius+px) : (px+width-cornerRadius);
        int yPos = (height/2)+py;
                        
        float distance = sqrt((float)(x-xPos)*(float)(x-xPos)+(float)(y-yPos)*(float)(y-yPos));
        if(abs(distance) > height/2) return false;

    }
    return true;
}

void drawPanel(Panel *p, Screen *sc){

    for(int i = 0; i < p->height; i++){
        for(int j = 0; j < p->width; j++){
            int x = p->x+j;
            int y = p->y+i;

            p->coveredColor[(i*p->width)+j] = getPixelColor(sc, x, y);

            if(!withinCorner(x, y, p->x, p->y, p->width, p->height, p->cornerRadius)) continue;
            
            setPixelColor(sc, x, y, p->panelColor);
            setPixelZOrder(sc, x, y, p->zOrder);

        }
    }

    int yOffset = p->height-p->shadowYOffset;
    int xOffset = p->shadowXOffset;
    for(int i = 0; i < p->shadowLength; i++){
        for(int j = 0; j < p->width; j++){
            int x = p->x+j+xOffset;
            int y = p->y+i+yOffset;
            
            p->coveredColorShadow[(i*p->width)+j] = getPixelColor(sc, x, y);

            if(!withinCorner(x, y, p->x+xOffset, p->y+yOffset, p->width, p->shadowLength, p->cornerRadius)) continue;
            setPixelColor(sc, x, y, lerpColor(p->panelColor, getPixelColor(sc, x, y), 0.5f));
            
        }   
    }

}

void hidePanel(Panel *p, Screen *sc){
    int yOffset = p->height-p->shadowYOffset;
    int xOffset = p->shadowXOffset;
    for(int i = 0; i < p->height; i++){
        for(int j = 0; j < p->width; j++){
            int x = p->x+j;
            int y = p->y+i;
            if(x >= getScreenWidth(sc)) continue;
            if(y >= getScreenHeight(sc)) continue;

            setPixelColor(sc, x, y, p->coveredColor[(i*p->width)+j]);
            setPixelZOrder(sc, x, y, 0);

            if(i < p->shadowLength){
                int sx = p->x+j+xOffset;
                int sy = p->y+i+yOffset;
                setPixelColor(sc, sx, sy, p->coveredColorShadow[(i*p->width)+j]);
            }

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