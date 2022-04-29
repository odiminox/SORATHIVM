#pragma once

#define WIN32_LEAN_AND_MEAN
#define VC_EXTRALEAN

#ifndef UNICODE
#define UNICODE
#define UNICODE_WAS_DEFINED
#endif

#include <Windows.h>

#ifdef UNICODE_WAS_DEFINED
#undef UNICODE
#endif


LRESULT CALLBACK
WindowProc(HWND window,
    UINT message,
    WPARAM wparam,
    LPARAM lparam)
{
    LRESULT res = 0;

    switch (message)
    {
        case WM_KEYDOWN:
            if (wparam == VK_ESCAPE)
                PostQuitMessage(0);
            break;
        case WM_SIZE:
            break;
            case WM_CLOSE:
                PostQuitMessage(0);
            break;
        case WM_ACTIVATEAPP:
            break;
        case WM_DESTROY:
        {
            PostQuitMessage(0);
            return 0;
            break;
        }
        case WM_PAINT:
            break;
    }

    return DefWindowProc(window, message, wparam, lparam);
}


void blueprint_update(MSG& msg, HDC& dc)
{
  
}

int WINAPI
WinMain(HINSTANCE hinstance,
    HINSTANCE hprevinstance,
    LPSTR lpcmdline,
    int ncmdshow)
{
    HWND hwnd;
    WNDCLASSEX wc;

    HINSTANCE hdll = LoadLibrary(L"opengl32.dll");

    // clear out the window class for use
    ZeroMemory(&wc, sizeof(WNDCLASSEX));
    wc.cbSize = sizeof(WNDCLASSEX);
    wc.style = CS_HREDRAW | CS_VREDRAW;
    wc.lpfnWndProc = WindowProc;
    wc.hInstance = hinstance;
    wc.hCursor = LoadCursor(NULL, IDC_ARROW);
    wc.hbrBackground = (HBRUSH)COLOR_WINDOW;
    wc.lpszClassName = L"Blueprint";

    RegisterClassEx(&wc);

    hwnd = CreateWindowEx(NULL,
                          L"Blueprint Editor",
                          L"Blueprint Editor",
                          WS_OVERLAPPEDWINDOW,
                          300,    // x-position of the window
                          300,    // y-position of the window
                          500,    // width of the window
                          400,    // height of the window
                          NULL,
                          NULL,
                          hinstance,
                          NULL);

    HDC dc = GetDC(hwnd);

    ShowWindow(hwnd, ncmdshow);

    MSG msg;
    while (true) {
        if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE)) {
            if (msg.message == WM_QUIT)
                break;

            TranslateMessage(&msg);
            DispatchMessage(&msg);
        }

        SwapBuffers(dc);
    };

    return msg.wParam;
}