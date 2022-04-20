#pragma once

#include <stdint.h>
#include <stdio.h>

typedef float     f32;
typedef double    f64;

typedef int8_t    i8;
typedef int16_t   i16;
typedef int32_t   i32;
typedef int64_t   i64;

typedef uint8_t   u8;
typedef uint16_t  u16;
typedef uint32_t  u32;
typedef uint64_t  u64;

typedef size_t    usize;
typedef intptr_t  uword;

typedef char* STRING;
typedef const char* CONST_STRING;

void assert_handler(const char* msg, const char* file, int line)
{
    fprintf(stdout, "%s:%d:4: error: assertion \"%s\" failed in function %s\n", file, line, msg);
    abort();
}