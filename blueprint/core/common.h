#pragma once

#include "types.h"

#define PI 3.141592653589f

#define DEG2RAD(deg) ((deg)*PI/180.0f)

#define ASSERT(exp) \
    if (exp) { } \
    else \
    { \
        assert_handler(#exp, __FILE__, __LINE__); \
        (__debugbreak(), 1); \
    }

// Pulled from winnt.h
#ifndef FORCEINLINE
#if (_MSC_VER >= 1200)
#define FORCEINLINE __forceinline
#else
#define FORCEINLINE __inline
#endif
#endif