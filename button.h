#ifndef BUTTON_H
#define BUTTON_H


#ifdef _cplusplus
extern "C" {
#endif

#include "stdint.h"


typedef struct ui_button UIButton;

UIButton *createButton(int x, int y, int width, int height, void *onClick);
void destroyButton(UIButton *btn);

void drawButton(UIButton *btn, uint32_t *pixels);

/*@brief If click is true and pointer is hovering over button onClick is called*/
void checkButton(UIButton *btn, bool click);


#ifdef _cplusplus
} //extern "C"
#endif


#endif //BUTTON_H