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
FORCEINLINE v2 operator /=(v2& a, f32 s) { return { a.x /= s, a.y /= s }; }
FORCEINLINE bool operator ==(const v2& a, const v2& b) { a.x == b.x && a.y == b.y; }
FORCEINLINE bool operator !=(const v2& a, const v2& b) { a.x != b.x || a.y != b.y; }

FORCEINLINE f32 magnitude(const v2& v) { return sqrt((v.x * v.x) + (v.y * v.y)); }
FORCEINLINE v2 normalise(const v2& v) { return v / magnitude(v); }
FORCEINLINE v2 abs(const v2& a) { return { abs(a.x), abs(a.y) }; }
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
FORCEINLINE v3 operator /=(v3& a, f32 s) { return { a.x /= s, a.y /= s, a.z /= s }; }
FORCEINLINE bool operator ==(const v3& a, const v3& b) { a.x == b.x && a.y == b.y && a.z == b.z; }
FORCEINLINE bool operator !=(const v3& a, const v3& b) { a.x != b.x || a.y != b.y || a.z != b.z; }

FORCEINLINE f32 magnitude(const v3 v) { return sqrt((v.x * v.x) + (v.y * v.y) + (v.z * v.z)); }
FORCEINLINE v3 normalise(const v3& v) { return v / magnitude(v); }
FORCEINLINE v3 abs(const v3& a) { return { abs(a.x), abs(a.y), abs(a.z) }; }
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

  FORCEINLINE f32& operator ()(const i16 i, const i16 j)
  {
      return table[i][j];
  }

  FORCEINLINE const f32& operator ()(const i16 i, const i16 j) const
  {
      return table[i][j];
  }
};

FORCEINLINE v2 operator *(const m4& m, const v2& v)
{
    const f32 x = m(0, 0) * v.x + m(0, 1) * v.y + m(0, 2);
    const f32 y = m(1, 0) * v.x + m(1, 1) * v.y + m(1, 2);
    const f32 z = m(2, 0) * v.x + m(2, 1) * v.y + m(2, 2);
    const f32 w = m(3, 0) * v.x + m(3, 1) * v.y + m(3, 3);

    return { x, y };
}

FORCEINLINE v3 operator *(const m4& m, const v3& v)
{
    const f32 x = m(0, 0) * v.x + m(0, 1) * v.y + m(0, 2) * v.z + m(0, 3);
    const f32 y = m(1, 0) * v.x + m(1, 1) * v.y + m(1, 2) * v.z + m(1, 3);
    const f32 z = m(2, 0) * v.x + m(2, 1) * v.y + m(2, 2) * v.z + m(2, 3);
    const f32 w = m(3, 0) * v.x + m(3, 1) * v.y + m(3, 3) * v.z + m(3, 3);

    return { x, y, z };
}

FORCEINLINE v4 operator *(const m4& m, const v4& v)
{
    const float x = m(0, 0) * v.x + m(0, 1) * v.y + m(0, 2) * v.z + m(0, 3) * v.w;
    const float y = m(1, 0) * v.x + m(1, 1) * v.y + m(1, 2) * v.z + m(1, 3) * v.w;
    const float z = m(2, 0) * v.x + m(2, 1) * v.y + m(2, 2) * v.z + m(2, 3) * v.w;
    const float w = m(3, 0) * v.x + m(3, 1) * v.y + m(3, 3) * v.z + m(3, 3) * v.w;

    return { x, y, z, w };
}

FORCEINLINE m4 operator *(m4& a, m4& b)
{
    // Row 1
    const float m00 = a(0, 0) * b(0, 0) + a(0, 1) * b(1, 0) + a(0, 2) * b(2, 0) + a(0, 3) * b(3, 0);
    const float m01 = a(0, 0) * b(0, 1) + a(0, 1) * b(1, 1) + a(0, 2) * b(2, 1) + a(0, 3) * b(3, 1);
    const float m02 = a(0, 0) * b(0, 2) + a(0, 1) * b(1, 2) + a(0, 2) * b(2, 2) + a(0, 3) * b(3, 2);
    const float m03 = a(0, 0) * b(0, 3) + a(0, 1) * b(1, 3) + a(0, 2) * b(2, 3) + a(0, 3) * b(3, 3);

    // Row 2
    const float m10 = a(1, 0) * b(0, 0) + a(1, 1) * b(1, 0) + a(1, 2) * b(2, 0) + a(1, 3) * b(3, 0);
    const float m11 = a(1, 0) * b(0, 1) + a(1, 1) * b(1, 1) + a(1, 2) * b(2, 1) + a(1, 3) * b(3, 1);
    const float m12 = a(1, 0) * b(0, 2) + a(1, 1) * b(1, 2) + a(1, 2) * b(2, 2) + a(1, 3) * b(3, 2);
    const float m13 = a(1, 0) * b(0, 3) + a(1, 1) * b(1, 3) + a(1, 2) * b(2, 3) + a(1, 3) * b(3, 3);

    // Row 3
    const float m20 = a(2, 0) * b(0, 0) + a(2, 1) * b(1, 0) + a(2, 2) * b(2, 0) + a(2, 3) * b(3, 0);
    const float m21 = a(2, 0) * b(0, 1) + a(2, 1) * b(1, 1) + a(2, 2) * b(2, 1) + a(2, 3) * b(3, 1);
    const float m22 = a(2, 0) * b(0, 2) + a(2, 1) * b(1, 2) + a(2, 2) * b(2, 2) + a(2, 3) * b(3, 2);
    const float m23 = a(2, 0) * b(0, 3) + a(2, 1) * b(1, 3) + a(2, 2) * b(2, 3) + a(2, 3) * b(3, 3);

    // Row 4
    const float m30 = a(3, 0) * b(0, 0) + a(3, 1) * b(1, 0) + a(3, 2) * b(2, 0) + a(3, 3) * b(3, 0);
    const float m31 = a(3, 0) * b(0, 1) + a(3, 1) * b(1, 1) + a(3, 2) * b(2, 1) + a(3, 3) * b(3, 1);
    const float m32 = a(3, 0) * b(0, 2) + a(3, 1) * b(1, 2) + a(3, 2) * b(2, 2) + a(3, 3) * b(3, 2);
    const float m33 = a(3, 0) * b(0, 3) + a(3, 1) * b(1, 3) + a(3, 2) * b(2, 3) + a(3, 3) * b(3, 3);

    return { m00, m01, m02, m03,
             m10, m11, m12, m13,
             m20, m21, m22, m23,
             m30, m31, m32, m33 };
}



FORCEINLINE f32 m4_determinant(const m4& m)
{
    return m(0, 0) * m(1, 1) * m(2, 2) - m(1, 2) * m(2, 1) +
        m(0, 1) * m(1, 2) * m(2, 0) - m(1, 0) * m(2, 2) +
        m(2, 0) * m(1, 0) * m(2, 1) - m(1, 1) * m(2, 0);
}