#pragma once

//#define GL_GLEXT_PROTOTYPES

#include <gl/GL.h>
#include "khrplatform.h"
#include "glext.h"
#include "wglext.h"

#define GETPROC(proc) (void*)wglGetProcAddress(proc);

PFNWGLCHOOSEPIXELFORMATARBPROC wglChoosePixelFormatARB;
PFNWGLCREATECONTEXTATTRIBSARBPROC wglCreateContextAttribsARB;
PFNGLGENBUFFERSPROC glGenBuffers;
PFNGLBINDBUFFERPROC glBindBuffer;
PFNGLBUFFERDATAPROC glBufferData;