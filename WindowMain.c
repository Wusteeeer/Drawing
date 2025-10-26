#include <stdio.h>
#include "string.h"
#include "math.h"
#include "stdint.h" 
#include "stdbool.h"
#include "c_util.h"
#include "vector.h"
#include "screen.h"
#include "brush.h"
#include "button.h"
#include "panel.h"
#include "dshape.h"

#define WIDTH 800
#define HEIGHT 600

#define ICONWIDTH 320
#define ICONHEIGHT 320

static Screen *sc;
static Brush *brush;
static UIButton *exportButton;
static Panel *testPanel;

static Screen *iconSc;
static UIButton *iconWindowButton;
static Brush *iconBrush;

static Vector *previousMouse, *currentMouse;

/*---------------------------------------

    Pallette from lospec 
        https://lospec.com/palette-list/mana-rift

---------------------------------------*/

#define PALETTE1 0xFFC5BDE5
#define PALETTE2 0xFF968FCC
#define PALETTE3 0xFF5760C7
#define PALETTE4 0xFF263997
#define PALETTE5 0xFF13234E


/*---------------------------------------

    Own colors

---------------------------------------*/




#ifdef _WIN32

/*----------------------------------------------------

    Creates a window for Windows (32 and 64 bit systems)

----------------------------------------------------*/

#include "windows.h"

int createWindow(WNDCLASS *wndclass, HWND handle, HINSTANCE hInstance, char *name, int iCmdShow, int height, int width, int x, int y, void *proc){

    wndclass->style = CS_HREDRAW | CS_VREDRAW;
    wndclass->lpfnWndProc = proc;
    wndclass->cbClsExtra = 0;
    wndclass->cbWndExtra = 0;
    wndclass->hInstance = hInstance;
    wndclass->hIcon = LoadIcon(NULL, IDI_APPLICATION);
    wndclass->hCursor = LoadCursor(NULL, IDC_ARROW);
    wndclass->hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH);
    wndclass->lpszMenuName = NULL;
    wndclass->lpszClassName = name;

    if(!RegisterClass(wndclass)){
        MessageBox(NULL, TEXT("This program requires windows NT"), name, MB_ICONERROR);
        return 0;
    }

    handle = CreateWindow(name, TEXT("Icon Creator"), WS_OVERLAPPEDWINDOW, x, y, width+15, height+15, NULL, NULL, hInstance, NULL);
    ShowWindow(handle, iCmdShow);

}
static bool mainWindowOpen = false, iconWindowOpen = false;
static bool createIconWindow = false;

void exportDrawing(){
}

void iconWindowCb(){

    if(createIconWindow || iconWindowOpen) return;
    createIconWindow = true;
}

void cleanupEnv(){
    destroyBrush(brush);
    destroyButton(exportButton);
    destroyScreen(sc);
    destroyScreen(iconSc);
    destroyBrush(iconBrush);
    destroyButton(iconWindowButton);
    destroyVector(previousMouse);
    destroyVector(currentMouse);

    destroyPanel(testPanel);
}

void initializeEnv(){
    sc = createScreen(WIDTH, HEIGHT, BACKGROUND);
    brush = createBrush(BT_CIRCLE, 20, PALETTE1, 0);
    exportButton = createButton(10, 10, WIDTH-20, 20, exportDrawing, BLUE, 1);
    drawButton(exportButton, sc, WIDTH, HEIGHT, 10);

    iconSc = createScreen(ICONWIDTH, ICONHEIGHT, BACKGROUND);
    iconWindowButton = createButton(WIDTH/2, HEIGHT/2, 100, 100, iconWindowCb, PALETTE2, 1);
    drawButton(iconWindowButton, sc, WIDTH, HEIGHT, 20);
    iconBrush = createBrush(BT_CIRCLE, 10, PALETTE1, 0);

    previousMouse = createVector(2, V2(0,0));
    currentMouse = createVector(2, V2(0,0));

    testPanel = createPanel((WIDTH/2)+200, HEIGHT/2, 100, 100, 20, 1, PALETTE3);
    flipPanel(testPanel, sc);

}

LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);
LRESULT CALLBACK IconProc(HWND, UINT, WPARAM, LPARAM);


double testFunc1(double val){
    //x(t) = (a + b) cost − b cos((a/b + 1)t)
    float a = 143.6f;
    float b = 31.25f;
    float ab = a + b;
    float aOb = (a/b)+1;
    return (((ab)*cos(val))-(b*cos(aOb*val)))+WIDTH/2;
}

double testFunc2(double val){
    //y(t) = (a + b)sin t − b sin((a/b + 1)t)
    float a = 143.6f;
    float b = 31.25f;
    float ab = a + b;
    float aOb = (a/b)+1;
    return ((ab)*sin(val))-(b*sin(aOb*val))+HEIGHT/2;
}

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, 
                   PSTR szCmdLine, int iCmdShow)
{

    MSG msg;
    HWND mainHandle;
    WNDCLASS wndclass;

    HWND iconHandle;
    WNDCLASS iconclass;

    wndclass.style = CS_HREDRAW | CS_VREDRAW;
    wndclass.lpfnWndProc = WndProc;
    wndclass.cbClsExtra = 0;
    wndclass.cbWndExtra = 0;
    wndclass.hInstance = hInstance;
    wndclass.hIcon = LoadIcon(NULL, IDI_APPLICATION);
    wndclass.hCursor = LoadCursor(NULL, IDC_ARROW);
    wndclass.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH);
    wndclass.lpszMenuName = NULL;
    wndclass.lpszClassName = "window 1";

    if(!RegisterClass(&wndclass)){
        MessageBox(NULL, TEXT("This program requires windows NT"), wndclass.lpszClassName, MB_ICONERROR);
        return 0;
    }

    mainHandle = CreateWindow(wndclass.lpszClassName, TEXT("Drawing"), WS_OVERLAPPEDWINDOW, 0,0,WIDTH+15, HEIGHT+15, NULL, NULL, hInstance, NULL);
    ShowWindow(mainHandle, iCmdShow);    
    initializeEnv();

    Vector *v1 = createVector(2, V2(100, 200));
    Vector *v2 = createVector(2, V2(300, 300));
    draw_rectangle(sc, v1, v2, 5, ARGB(255, 255, 0, 0), 0);
    destroyVector(v1);
    destroyVector(v2);

    Brush *testBrush = createBrush(BT_CIRCLE, 5, ARGB(255, 100, 100, 150), 2);
    draw_p_curve_2D(sc, testFunc1, testFunc2, 0, PI*16, testBrush, 0.01f, true);
    destroyBrush(testBrush);

    bool running = true;
    int nrIcon = 0;
    while(running){
        if(GetMessage(&msg, NULL, 0, 0)){
            TranslateMessage(&msg);
            DispatchMessage(&msg);        
        }

        if(createIconWindow){
            char name[100];
            sprintf(name, "icon%d", nrIcon++);
            createWindow(&iconclass, iconHandle, hInstance, name, iCmdShow, ICONHEIGHT, ICONWIDTH, 0, 0, IconProc);
            createIconWindow = false;
        }

        if(!mainWindowOpen && !iconWindowOpen){
            running = false;
        }
    }
    

    cleanupEnv();
    return msg.wParam;
}

static void checkButtons(WPARAM wParam, LPARAM lParam){
    int mouseX = lParam&0xFFFF;
    int mouseY = (lParam>>16)&0xFFFF;
            
    checkButton(exportButton, wParam == MK_LBUTTON, mouseX, mouseY);
    checkButton(iconWindowButton, wParam==MK_LBUTTON, mouseX, mouseY);
}

static void drawAt(WPARAM wParam, LPARAM lParam, Screen *sc, Brush *br){

    if(wParam != MK_LBUTTON) return;
    int mouseX = lParam&0xFFFF;
    int mouseY = (lParam>>16)&0xFFFF;

    draw_line_2D(sc, brush, currentMouse, previousMouse);

    setValues(currentMouse, V2(getX(previousMouse), getY(previousMouse)));
    setValues(previousMouse, V2(mouseX, mouseY));
}


LRESULT CALLBACK WndProc(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam){
    HDC hdc;
    PAINTSTRUCT ps;
    RECT rect;
    int mouseX=0, mouseY=0;

    switch(message){
        case WM_CREATE:
            mainWindowOpen = true;
        return 0;
        case WM_KEYDOWN:
        if (wParam == VK_SPACE)
        {
            flipPanel(testPanel, sc);
        }
        return 0;
        case WM_LBUTTONDOWN:
            setValues(previousMouse, V2(lParam&0xFFFF, (lParam>>16)&0xFFFF));
            //Add 1 pixel so the distance is great enough to draw this pixel offset is fixed when you the actually draw
            setValues(currentMouse, V2((lParam&0xFFFF)+1, ((lParam>>16)&0xFFFF)+1));

            checkButtons(wParam, lParam);
            drawAt(wParam, lParam, sc, brush);   
        return 0;
        case WM_MOUSEMOVE:
            drawAt(wParam, lParam, sc, brush);
        case WM_PAINT:
                
            hdc = GetDC(hwnd);
            HDC memdc = CreateCompatibleDC(hdc);
            HBITMAP hbitmap = CreateCompatibleBitmap(hdc, WIDTH, HEIGHT);
            SetBitmapBits(hbitmap, WIDTH*HEIGHT*sizeof(uint32_t), getPixels(sc));
            SelectObject(memdc, hbitmap);

            BitBlt(hdc, 0, 0, WIDTH, HEIGHT, memdc, 0, 0, SRCCOPY);

            ReleaseDC(hwnd, hdc);
            DeleteDC(memdc);
            DeleteObject(hbitmap);
        return 0;
        case WM_DESTROY:
        mainWindowOpen = false;
        return 0;
    }
    return DefWindowProc(hwnd, message, wParam, lParam);
}

LRESULT CALLBACK IconProc(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam){
    HDC hdc;
    switch(message){
        case WM_CREATE:
            iconWindowOpen = true;
        return 0;
        case WM_LBUTTONDOWN:
            setValues(previousMouse, V2(lParam&0xFFFF, (lParam>>16)&0xFFFF));
            //Add 1 pixel so the distance is great enough to draw this pixel offset is fixed when you the actually draw
            setValues(currentMouse, V2((lParam&0xFFFF)+1, ((lParam>>16)&0xFFFF)+1));
            drawAt(wParam, lParam, iconSc, iconBrush);   
        return 0;
        case WM_MOUSEMOVE:
            drawAt(wParam, lParam, iconSc, iconBrush); 
        case WM_PAINT:
            hdc = GetDC(hwnd);
            HDC memdc = CreateCompatibleDC(hdc);
            HBITMAP hbitmap = CreateCompatibleBitmap(hdc, ICONWIDTH, ICONHEIGHT);
            SetBitmapBits(hbitmap, ICONWIDTH*ICONHEIGHT*sizeof(uint32_t), getPixels(iconSc));
            SelectObject(memdc, hbitmap);

            BitBlt(hdc, 0, 0, ICONWIDTH, ICONHEIGHT, memdc, 0, 0, SRCCOPY);

            ReleaseDC(hwnd, hdc);
            DeleteDC(memdc);
            DeleteObject(hbitmap);
        return 0;
        case WM_DESTROY:
        iconWindowOpen = false;
        return 0;
    }
    return DefWindowProc(hwnd, message, wParam, lParam);
}


#elif unix

/*----------------------------------------------------

    Creates a window for Unix systems

----------------------------------------------------*/



#elif __APPLE__

/*----------------------------------------------------

    Creates a window for Mac systems

----------------------------------------------------*/



#endif