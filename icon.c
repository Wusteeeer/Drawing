#include <stdio.h>
#include <stdint.h>
#include <stdbool.h>
#include <pthread.h>
#include "icon.h"
#include "c_util.h"


//TODO: Figure out how to hide and show window
LRESULT CALLBACK iconProc(HWND, UINT, WPARAM, LPARAM);

static Screen *iconSc;
static bool running = false;
static bool createWindow = false;

void *createIconWindow(HINSTANCE hInstance, int iCmdShow, Screen *iSc){
    iconSc = iSc;

    static TCHAR iconName[] = TEXT("Icon");
    HWND iconHandle;
    MSG msg;
    WNDCLASS iconclass;
    iconclass.style = CS_HREDRAW | CS_VREDRAW;
    iconclass.lpfnWndProc = iconProc;
    iconclass.cbClsExtra = 0;
    iconclass.cbWndExtra = 0;
    iconclass.hInstance = hInstance;
    iconclass.hIcon = LoadIcon(NULL, IDI_APPLICATION);
    iconclass.hCursor = LoadCursor(NULL, IDC_ARROW);
    iconclass.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH);
    iconclass.lpszMenuName = NULL;
    iconclass.lpszClassName = iconName;
    if(!RegisterClass(&iconclass)){
        MessageBox(NULL, TEXT("This program requires windows NT"), iconName, MB_ICONERROR);
        return 0;
    }
    iconHandle = CreateWindow(iconName, TEXT("Icon"), WS_OVERLAPPEDWINDOW, 0,0, ICONWIDTH, ICONHEIGHT, NULL, NULL, hInstance, NULL);
    ShowWindow(iconHandle, iCmdShow);
    UpdateWindow(iconHandle);
    
    while(GetMessage(&msg, NULL, 0, 0)){
        
        TranslateMessage(&msg);
        DispatchMessage(&msg);
        
    }
    
    
    
    return NULL;
}

void closeWindow(){
    running = false;
}

void openWindow(){
    running = true;
}

LRESULT CALLBACK iconProc(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam){
    HDC hdc;

    switch(message){
        case WM_CREATE:
        printf("Created icon window!\n");
        return 0;
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
        PostQuitMessage(0);
        return 0;

    }
    return DefWindowProc(hwnd, message, wParam, lParam);
}