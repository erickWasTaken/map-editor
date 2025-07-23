#ifdef APP
#pragma once
#include "Math.h"

#define vec2 Vec2
#define ivec2 Ivec2
#define vec4 Vec4

#else
#define BIT(i) 1 << i

#endif

struct Transform{
    struct vec2 pos;
    struct vec2 scale;
    
    unsigned int shaderID;
};
