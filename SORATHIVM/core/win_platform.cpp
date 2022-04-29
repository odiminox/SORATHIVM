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

#include "getprocs.h"
#include "graphics.h"
#include "memory.h"
extern "C"{
    #include "libct.h"
}

// set rounding mode to truncate
//  from https://web.archive.org/web/20160304215813/http://www.musicdsp.org/showone.php?id=246
static short control_word;
static short control_word2;

inline void SetFloatingPointRoundingToTruncate()
{
    __asm
    {
        fstcw   control_word                // store fpu control word
        mov     dx, word ptr [control_word]
        or      dx, 0x0C00                  // rounding: truncate
        mov     control_word2, dx
        fldcw   control_word2               // load modfied control word
    }
}

HMODULE gl_module;


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
    SetFloatingPointRoundingToTruncate();

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
    wc.lpszClassName = L"SORATHIVM";

    RegisterClassEx(&wc);

    hwnd = CreateWindowEx(NULL,
                          L"SORATHIVM",
                          L"SORATHIVM",
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

   wglChoosePixelFormatARB = (PFNWGLCHOOSEPIXELFORMATARBPROC)GETPROC("wglChoosePixelFormatARB");
   wglCreateContextAttribsARB = (PFNWGLCREATECONTEXTATTRIBSARBPROC)GETPROC("wglCreateContextAttribsARB");
   glGenBuffers = (PFNGLGENBUFFERSPROC)GETPROC("glGenBuffers");
   glBindBuffer = (PFNGLBINDBUFFERPROC)GETPROC("glBindBuffer");
   glBufferData = (PFNGLBUFFERDATAPROC)GETPROC("glBufferData");

    HWND hwnd_real = CreateWindowEx(NULL,
                                    L"SORATHIVM",
                                    L"SORATHIVM",
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

    //wglMakeCurrent(dc, NULL);
    //wglDeleteContext(rc);
    //ReleaseDC(hwnd, dc);
    //DestroyWindow(hwnd);
    wglMakeCurrent(dc_real, rc_real);

    ShowWindow(hwnd_real, ncmdshow);

    MemArena* arena = NULL;

    Vertex* vert1 = NULL;
    Vertex vert2;
    Vertex vert3;

    arena = alloc_arena(MEGABYTES(20));

    MemBlock* block1 = alloc_block(arena, sizeof(*vert1));

    vert1 = (Vertex*)block1;

    vert1->pos.x = -1.0f;
    vert1->pos.y = -1.0f;
    vert1->pos.z = 0.0f;

    vert2.pos.x = 1.0f;
    vert2.pos.y = -1.0f;
    vert2.pos.z = 0.0f;

    vert3.pos.x = 0.0f;
    vert3.pos.y = 1.0f;
    vert3.pos.z = 0.0f;


    blueprint_init();

    GLuint vertex_buffer;
    glGenBuffers(1, &vertex_buffer);
    glBindBuffer(GL_ARRAY_BUFFER, vertex_buffer);

    u32 vert_size = sizeof(vert1->pos);
    u32 vert_buffer_size =  sizeof(vert1->pos) * 3;

    /*const GLfloat buffer_data[] = {
       vert1->pos.x, vert1->pos.y, vert1->pos.z,
       vert2->pos.x, vert2->pos.y, vert2->pos.z,
       vert3->pos.x, vert3->pos.y, vert3->pos.z,
    };

    glBufferData(GL_ARRAY_BUFFER, sizeof(vert_buffer_size), buffer_data, GL_STATIC_DRAW);*/


    MSG msg;
    blueprint_update(msg, dc_real);

    free_arena(arena);

    return msg.wParam;
}

extern "C" void __cdecl WinMainCRTStartup()
{
    int argc = _init_args();
    _init_atexit();
    _initterm(__xc_a, __xc_z);         // Call C++ constructors

    int ret = WinMain((HINSTANCE)0x400000,0, 0,SW_SHOWDEFAULT);

    _doexit();
    ExitProcess(ret);
}