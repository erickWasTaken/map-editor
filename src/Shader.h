#ifdef ENGINE
#pragma once

#include "Math.h"
#define vec2 Vec2
#define ivec2 IVec2
// #define vec4 Vec4

#else
#define BIT(i) 1 << i
#endif

struct Transform{
    ivec2 position;
    vec2 speed;
};
