#ifndef BUTTON_H
#define BUTTON_H


#ifdef _cplusplus
extern "C" {
#endif

#include "stdint.h"
#include "c_util.h"
#include "screen.h"


typedef struct ui_button UIButton;

UIButton *createButton(int x, int y, int width, int height, void *onClick, COLOR color, U_BYTE zOrder);
void destroyButton(UIButton *btn);

void drawButton(UIButton *btn, Screen *sc, int screenWidth, int screenHeight, int cornerRadius);

/*@brief If click is true and pointer is hovering over button onClick is called*/
void checkButton(UIButton *btn, bool click, int mouseX, int mouseY);


#ifdef _cplusplus
} //extern "C"
#endif


#endif //BUTTON_H