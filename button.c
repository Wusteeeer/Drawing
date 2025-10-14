#include <stdio.h>
#include <stdlib.h>
#include "stdbool.h"
#include "button.h"

typedef struct ui_button{
    int x, y;
    int width, height;
    void (*onClick)();
    COLOR color;
    U_BYTE zOrder;
}UIButton;

UIButton *createButton(int x, int y, int width, int height, void *onClick, COLOR color, U_BYTE zOrder){
    UIButton *btn = malloc(sizeof(UIButton));
    btn->width = width;
    btn->height = height;
    btn->x = x;
    btn->y = y;
    btn->color = color;
    btn->onClick = onClick;
    btn->zOrder = zOrder;
    return btn;
}

void drawButton(UIButton *btn, Screen *sc, int screenWidth, int screenHeight){
    
    for(int h = 0; h < btn->height; h++){
        if(btn->y + h > screenHeight) continue;
        for(int w = 0; w < btn->width; w++){
            if(btn->x+w > screenWidth) continue;
            
            setPixelColor(sc, btn->x+w, btn->y+h, btn->color);
            setPixelZOrder(sc, btn->x+w, btn->y+h, btn->zOrder);
        }
    }

}

void destroyButton(UIButton *btn){
    free(btn);
}

/*@brief If click is true and pointer is hovering over button onClick is called*/
void checkButton(UIButton *btn, bool click, int mouseX, int mouseY){
    if(click && (mouseX >= btn->x && mouseX <= btn->x+btn->width && mouseY >= btn->y && mouseY <= btn->y+btn->height)){
        btn->onClick();
    }
}