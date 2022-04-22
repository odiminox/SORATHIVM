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

void blueprint_init()
{
    usize aligned = align(3);
    ASSERT(aligned == 8);
    aligned = align(12);
    ASSERT(aligned == 16);

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

void blueprint_update(MSG& msg, HDC& dc)
{
    while (true) {
        if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE)) {
            if (msg.message == WM_QUIT)
                break;

            TranslateMessage(&msg);
            DispatchMessage(&msg);
        }

        glClearColor(0.129f, 0.586f, 0.949f, 1.0f); // rgb(33,150,243)
        glClear(GL_COLOR_BUFFER_BIT);

        SwapBuffers(dc);
    }
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

    HDC dc = GetDC(hwnd);

    PIXELFORMATDESCRIPTOR pfd;
    ZeroMemory(&pfd, sizeof(pfd));
    pfd.nSize = sizeof(pfd);
    pfd.nVersion = 1;
    pfd.dwFlags = PFD_DRAW_TO_WINDOW | PFD_SUPPORT_OPENGL | PFD_DOUBLEBUFFER;
    pfd.iPixelType = PFD_TYPE_RGBA;
    pfd.cColorBits = 32;
    pfd.cAlphaBits = 8;
    pfd.cDepthBits = 24;

    int pfdid = ChoosePixelFormat(dc, &pfd);

    SetPixelFormat(dc, pfdid, &pfd);

    HGLRC rc = wglCreateContext(dc);
    wglMakeCurrent(dc, rc);

    PFNWGLCHOOSEPIXELFORMATARBPROC wglChoosePixelFormatARB = nullptr;
    wglChoosePixelFormatARB = reinterpret_cast<PFNWGLCHOOSEPIXELFORMATARBPROC>(wglGetProcAddress("wglChoosePixelFormatARB"));

    PFNWGLCREATECONTEXTATTRIBSARBPROC wglCreateContextAttribsARB = nullptr;
    wglCreateContextAttribsARB = reinterpret_cast<PFNWGLCREATECONTEXTATTRIBSARBPROC>(wglGetProcAddress("wglCreateContextAttribsARB"));

    HWND hwnd_real = CreateWindowEx(NULL,
                                    L"Blueprint",
                                    L"Blueprint",
                                    WS_OVERLAPPEDWINDOW | WS_SYSMENU | WS_CLIPSIBLINGS | WS_CLIPCHILDREN,
                                    300,    // x-position of the window
                                    300,    // y-position of the window
                                    500,    // width of the window
                                    400,    // height of the window
                                    NULL,
                                    NULL,
                                    hinstance,
                                    NULL);

    HDC dc_real = GetDC(hwnd_real);

    const int pixel_attribs[] = {
        WGL_DRAW_TO_WINDOW_ARB, GL_TRUE,
        WGL_SUPPORT_OPENGL_ARB, GL_TRUE,
        WGL_DOUBLE_BUFFER_ARB, GL_TRUE,
        WGL_PIXEL_TYPE_ARB, WGL_TYPE_RGBA_ARB,
        WGL_ACCELERATION_ARB, WGL_FULL_ACCELERATION_ARB,
        WGL_COLOR_BITS_ARB, 32,
        WGL_ALPHA_BITS_ARB, 8,
        WGL_DEPTH_BITS_ARB, 24,
        WGL_STENCIL_BITS_ARB, 8,
        WGL_SAMPLE_BUFFERS_ARB, GL_TRUE,
        WGL_SAMPLES_ARB, 4,
        0
    };

    int pixel_format_id; UINT num_formats;
    bool status = wglChoosePixelFormatARB(dc_real, pixel_attribs,
                                          NULL,
                                          1,
                                          &pixel_format_id,
                                          &num_formats);

    PIXELFORMATDESCRIPTOR pfd_real;
    DescribePixelFormat(dc_real, pixel_format_id, sizeof(pfd_real), &pfd_real);
    SetPixelFormat(dc_real, pixel_format_id, &pfd_real);

    const int major_min = 3, minor_min = 3;
    int  context_attribs[] = {
        WGL_CONTEXT_MAJOR_VERSION_ARB, major_min,
        WGL_CONTEXT_MINOR_VERSION_ARB, minor_min,
        WGL_CONTEXT_PROFILE_MASK_ARB, WGL_CONTEXT_CORE_PROFILE_BIT_ARB,
        0
    };

    HGLRC rc_real = wglCreateContextAttribsARB(dc_real, 0, context_attribs);

    wglMakeCurrent(dc_real, rc_real);

    ShowWindow(hwnd_real, ncmdshow);

    blueprint_init();

    MSG msg;
    blueprint_update(msg, dc_real);

    return msg.wParam;
}

