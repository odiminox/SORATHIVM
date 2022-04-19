#pragma once

#include <Windows.h>

LRESULT CALLBACK
WindowProc(HWND window,
    UINT message,
    WPARAM wparam,
    LPARAM lparam)
{
    LRESULT res = 0;

    switch (message)
    {
    case WM_SIZE:
        break;
    case WM_CLOSE:
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

int WINAPI
WinMain(HINSTANCE hinstance,
    HINSTANCE hprevinstance,
    LPSTR lpcmdline,
    int ncmdshow)
{
    HWND hWnd;
    WNDCLASSEX wc;

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

    hWnd = CreateWindowEx(NULL,
        L"Blueprint",
        L"Blueprint",
        WS_OVERLAPPEDWINDOW,
        300,    // x-position of the window
        300,    // y-position of the window
        500,    // width of the window
        400,    // height of the window
        NULL,
        NULL,
        hinstance,
        NULL);

    ShowWindow(hWnd, ncmdshow);

    MSG msg;

    // wait for the next message in the queue, store the result in 'msg'
    while (GetMessage(&msg, NULL, 0, 0))
    {
        TranslateMessage(&msg);

        DispatchMessage(&msg);
    }

    return msg.wParam;
}