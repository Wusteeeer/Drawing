#include <stdio.h>
#include "math.h"
#include "stdint.h" 
#include "brush.h"

#define WIDTH 700
#define HEIGHT 500

#define PIXELCOLS 32
#define PIXELROWS 32

static uint32_t pixels[WIDTH*HEIGHT];
static Brush *brush;
 
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

    brush = createBrush(BT_CIRCLE, 50, BLUE);

    hwnd = CreateWindow(szAppName, TEXT("Hello World"), WS_OVERLAPPEDWINDOW, CW_USEDEFAULT, CW_USEDEFAULT, WIDTH, HEIGHT, NULL, NULL, hInstance, NULL);
    ShowWindow(hwnd, iCmdShow);
    UpdateWindow(hwnd);

    for(int i = 0; i < HEIGHT; i++){
        for(int j = 0; j < WIDTH; j++){
            
            pixels[i * WIDTH + j] = GREEN;
        }
    }

    while(GetMessage(&msg, NULL, 0, 0)){
       
        TranslateMessage(&msg);
        DispatchMessage(&msg);
     
    }

    destroyBrush(brush);

    return msg.wParam;
}

LRESULT CALLBACK WndProc(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam){
    HDC hdc;
    PAINTSTRUCT ps;
    RECT rect;

    switch(message){
        case WM_CREATE:
            printf("Created!\n");
        return 0;
        case WM_MOUSEMOVE:
            
            if(wParam != MK_LBUTTON) return 0;

            int mouseX = lParam&0xFFFF;
            int mouseY = (lParam>>16)&0xFFFF;

            draw(pixels, brush, mouseX, mouseY, WIDTH, HEIGHT);
            //pixels[mouseY*WIDTH+mouseX]=PALETTE1;

        case WM_PAINT:
                    
            hdc = GetDC(hwnd);
            HDC memdc = CreateCompatibleDC(hdc);
            HBITMAP hbitmap = CreateCompatibleBitmap(hdc, WIDTH, HEIGHT);
            SetBitmapBits(hbitmap, WIDTH*HEIGHT*sizeof(uint32_t), pixels);
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