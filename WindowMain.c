#include <stdio.h>
#include "math.h"
#include "stdint.h" 
#include "stdbool.h"
#include "c_util.h"
#include "screen.h"
#include "brush.h"
#include "button.h"

#define WIDTH 700
#define HEIGHT 500

#define PIXELCOLS 32
#define PIXELROWS 32


static Screen *sc;
static Brush *brush;
static UIButton *exportButton;
 
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

void exportDrawing(){
    printf("Clicked button!\n");
}

void cleanupEnv(){
    destroyBrush(brush);
    destroyButton(exportButton);
    destroyScreen(sc);
}

void initializeEnv(){
    sc = createScreen(WIDTH, HEIGHT, BACKGROUND);
    brush = createBrush(BT_CIRCLE, 50, PALETTE1, 0);
    exportButton = createButton((WIDTH/2)-50, (HEIGHT/2)-25, 100, 50, exportDrawing, BLUE, 1);
    drawButton(exportButton, sc, WIDTH, HEIGHT);
}

LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, 
                   PSTR szCmdLine, int iCmdShow)
{

    static TCHAR szAppName[] = TEXT("Hello");
    HWND hwnd;
    MSG msg;
    WNDCLASS wndclass;

    wndclass.style = CS_HREDRAW | CS_VREDRAW;
    wndclass.lpfnWndProc = WndProc;
    wndclass.cbClsExtra = 0;
    wndclass.cbWndExtra = 0;
    wndclass.hInstance = hInstance;
    wndclass.hIcon = LoadIcon(NULL, IDI_APPLICATION);
    wndclass.hCursor = LoadCursor(NULL, IDC_ARROW);
    wndclass.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH);
    wndclass.lpszMenuName = NULL;
    wndclass.lpszClassName = szAppName;

    if(!RegisterClass(&wndclass)){
        MessageBox(NULL, TEXT("This program requires windows NT"), szAppName, MB_ICONERROR);
        return 0;
    }

    initializeEnv();

    hwnd = CreateWindow(szAppName, TEXT("Hello World"), WS_OVERLAPPEDWINDOW, CW_USEDEFAULT, CW_USEDEFAULT, WIDTH, HEIGHT, NULL, NULL, hInstance, NULL);
    ShowWindow(hwnd, iCmdShow);
    UpdateWindow(hwnd);



    while(GetMessage(&msg, NULL, 0, 0)){
    

        TranslateMessage(&msg);
        DispatchMessage(&msg);
     
    }

    cleanupEnv();
    return msg.wParam;
}

static void checkButtons(WPARAM wParam, LPARAM lParam){
    int mouseX = lParam&0xFFFF;
    int mouseY = (lParam>>16)&0xFFFF;
            
    checkButton(exportButton, wParam == MK_LBUTTON, mouseX, mouseY);
}

static void drawAt(WPARAM wParam, LPARAM lParam){

    if(wParam != MK_LBUTTON) return;
    int mouseX = lParam&0xFFFF;
    int mouseY = (lParam>>16)&0xFFFF;
    
    draw(sc, brush, mouseX, mouseY, WIDTH, HEIGHT);
            
}

LRESULT CALLBACK WndProc(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam){
    HDC hdc;
    PAINTSTRUCT ps;
    RECT rect;
    int mouseX=0, mouseY=0;

    switch(message){
        case WM_CREATE:
            printf("Created!\n");
        return 0;
        case WM_LBUTTONDOWN:
            checkButtons(wParam, lParam);
            drawAt(wParam, lParam);   
        return 0;
        case WM_MOUSEMOVE:
            drawAt(wParam, lParam);
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
        PostQuitMessage(0);
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