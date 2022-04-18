#pragma once

#include "common.h"

#define PI 3.141592653589f

#define DEG2RAD(deg) ((deg)*PI/180.0f)

union v2
{
  f32 v[2];
  struct { f32 x, y; };
};

FORCEINLINE v2 operator +(const v2& a, const v2& b) { return { a.x + b.x, a.y + b.y }; }
FORCEINLINE v2 operator -(const v2& a, const v2& b) { return { a.x - b.x, a.y - b.y }; }
FORCEINLINE v2 operator *(const v2& a, const f32 s) { return { a.x * s, a.y * s }; }
FORCEINLINE v2 operator /(const v2& a, f32 s) { s = 1.0f / s; return { a.x / s, a.y / s }; }
FORCEINLINE v2 operator -(const v2& a) { return { -a.x, -a.y }; }

union v3
{
  f32 v[3];
  struct { f32 x, y, z; };
};

FORCEINLINE v3 operator +(const v3& a, const v3& b) { return { a.x + b.x, a.y + b.y, a.z + b.z }; }
FORCEINLINE v3 operator -(const v3& a, const v3& b) { return { a.x - b.x, a.y - b.y, a.z - b.z }; }
FORCEINLINE v3 operator *(const v3& a, const f32 s) { return { a.x * s, a.y * s, a.z * s }; }
FORCEINLINE v3 operator /(const v3& a, f32 s) { s = 1.0f / s; return { a.x / s, a.y / s, a.z * s }; }
FORCEINLINE v3 operator -(const v3& a) { return { -a.x, -a.y, -a.z }; }