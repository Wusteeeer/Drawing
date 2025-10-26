#ifndef PANEL_H
#define PANEL_H

#include "c_util.h"
#include "screen.h"

typedef struct panel Panel;

Panel *createPanel(int x, int y, int width, int height, int cornerRadius, U_BYTE zOrder, COLOR color, int shadowLength, int shadowXOffset, int shadowYOffset);
void destroyPanel(Panel *p);

void flipPanel(Panel *p, Screen *sc);

#endif