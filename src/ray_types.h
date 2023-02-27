#ifndef RAY_TYPES_H
#define RAY_TYPES_H

#include <cstdint>

#include "raylib.h"
#include "raymath.h"


#define int8   int8_t
#define uint8  uint8_t
#define int16  int16_t
#define uint16 uint16_t
#define int32  int32_t
#define uint32 uint32_t
#define int64  int64_t 
#define uint64 uint64_t


#define v2 Vector2
#define v3 Vector3
#define v4 Vector4

#if MY_DEBUG
// coppied from HandmadeHero project. Sorry 
#define Assert(Expression) if(!(Expression)) {*(volatile int *)0 = 0;}
#else
#define Assert(Expression)
#endif

#define ArrayCount(Array) (sizeof(Array) / sizeof((Array)[0]))

inline v2 Vec2()
{
    return {0.0f, 0.0f};
}

inline v2 Vec2(float x, float y)
{
    return {x, y};
}

inline v3 Vec3(float x, float y, float z)
{
    return {x, y, z};
}

inline v4 Vec4(float x, float y, float z, float w)
{
    return {x, y, z, w};
}

inline Rectangle Rec(float x, float y, float width, float height)
{
    return {x, y, width, height};
}

inline int Clamp(int value, int min, int max)
{
    if(value < min) return min;
    if(value > max) return max;
    return value;
}

#endif