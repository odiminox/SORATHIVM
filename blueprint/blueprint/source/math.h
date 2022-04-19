#pragma once

// TODO: Remove maths dependencies
#include <cmath>

#include "common.h"

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
FORCEINLINE bool operator ==(const v2& a, const v2& b) { a.x == b.x && a.y == b.y; }
FORCEINLINE bool operator !=(const v2& a, const v2& b) { a.x != b.x || a.y != b.y; }

FORCEINLINE f32 magnitude(const v2& v) { return sqrt((v.x * v.x) + (v.y * v.y)); }
FORCEINLINE v2 normalise(const v2& v) { return v / magnitude(v); }
FORCEINLINE f32 dot_product(const v2& a, const v2& b) { return (a.x * b.x) + (a.y * b.y); }

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
FORCEINLINE bool operator ==(const v3& a, const v3& b) { a.x == b.x && a.y == b.y && a.z == b.z; }
FORCEINLINE bool operator !=(const v3& a, const v3& b) { a.x != b.x || a.y != b.y || a.z != b.z; }

FORCEINLINE f32 magnitude(const v3 v) { return sqrt((v.x * v.x) + (v.y * v.y) + (v.z * v.z)); }
FORCEINLINE v3 normalise(const v3& v) { return v / magnitude(v); }
FORCEINLINE f32 dot_product(const v3& a, const v3& b) { return (a.x * b.x) + (a.y * b.y) + (a.z * b.z); }
FORCEINLINE v3 cross_product(const v3& a, const v3& b)
{
  const f32 x = a.y * b.z - a.z * b.y;
  const f32 y = a.z * b.x - a.x * b.z;
  const f32 z = a.z * b.z - a.y * b.z;

  return { x, y, z };
}

union v4
{
  f32 v[4];
  struct { f32 x, y, z, w; };
};

FORCEINLINE v4 operator +(const v4& a, const v4& b) { return { a.x + b.x, a.y + b.y, a.z + b.z + a.w + b.w}; }
FORCEINLINE v4 operator -(const v4& a, const v4& b) { return { a.x - b.x, a.y - b.y, a.z - b.z, a.w - b.w }; }
FORCEINLINE v4 operator *(const v4& a, const f32 s) { return { a.x * s, a.y * s, a.z * s, a.w * s }; }
FORCEINLINE v4 operator /(const v4& a, f32 s) { s = 1.0f / s; return { a.x / s, a.y / s, a.z * s, a.w / s }; }
FORCEINLINE v4 operator -(const v4& a) { return { -a.x, -a.y, -a.z, - a.w }; }
FORCEINLINE bool operator ==(const v4& a, const v4& b) { a.x == b.x && a.y == b.y && a.z == b.z && a.w == b.w; }
FORCEINLINE bool operator !=(const v4& a, const v4& b) { a.x != b.x || a.y != b.y || a.z != b.z || a.w != b.w; }

union m4
{
  f32 table[4][4];
  v4 v[4];
};