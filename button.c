#include <stdio.h>
#include <stdlib.h>
#include "stdbool.h"
#include "button.h"

typedef struct ui_button{
    int x, y;
    int width, height;
    void (*onClick)();
}UIButton;

UIButton *createButton(int x, int y, int width, int height, void *onClick){
    UIButton *btn = malloc(sizeof(UIButton));
    btn->width = width;
    btn->height = height;
    btn->x = x;
    btn->y = y;
    btn->onClick = onClick;

    return btn;
}

void drawButton(UIButton *btn, uint32_t *pixels){
    
}

void destroyButton(UIButton *btn){
    free(btn);
}

/*@brief If click is true and pointer is hovering over button onClick is called*/
void checkButton(UIButton *btn, bool click){
    if(click){
        btn->onClick();
    }
}