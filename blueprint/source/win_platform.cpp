#pragma once

#ifndef UNICODE
#define UNICODE
#define UNICODE_WAS_DEFINED
#endif

#include <Windows.h>

#ifdef UNICODE_WAS_DEFINED
#undef UNICODE
#endif

#include <gl/GL.h>
#include "khrplatform.h"
#include "glext.h"
#include "wglext.h"

#include "graphics.h"
#include "memory.h"


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

    usize aligned = align(3);
    ASSERT(aligned == 8);
    aligned = align(12);
    ASSERT(aligned == 16);

    {
        Vertex* vert = NULL;
        u32 vert_size = sizeof(*vert);
        MemArena* arena = alloc_arena(64);

        MemBlock* track = NULL;
        MemBlock* block = alloc_block(arena, vert_size);
        vert = (Vertex*)block;
        vert->pos.x = 1.0f;
        vert->pos.y = 2.0f;
        vert->pos.z = 3.0f;


        free_arena(arena);
    }

    MSG msg;

    // wait for the next message in the queue, store the result in 'msg'
    while (GetMessage(&msg, NULL, 0, 0))
    {
        TranslateMessage(&msg);

        DispatchMessage(&msg);
    }

    return msg.wParam;
}
