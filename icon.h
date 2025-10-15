#ifndef ICON_H
#define ICON_H

#include "screen.h"

#define ICONWIDTH 320
#define ICONHEIGHT 320

#ifdef _cplusplus
extern "C" {
#endif

#ifdef _WIN32

#include "windows.h"
void *createIconWindow(HINSTANCE hInstance, int iCmdShow, Screen *iSc);
void closeWindow();
void openWindow();

#elif unix

/*----------------------------------------------------

    Creates a window for Unix systems

----------------------------------------------------*/



#elif __APPLE__

/*----------------------------------------------------

    Creates a window for Mac systems

----------------------------------------------------*/



#endif

#ifdef _cplusplus
} //extern "C"
#endif


#endif