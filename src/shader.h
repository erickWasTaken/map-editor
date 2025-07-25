#ifdef APP
#pragma once
#include "Math.h"

#define vec2 struct Vec2
#define ivec2 struct Ivec2
#define vec4 struct Vec4

#else
#define BIT(i) 1 << i

#endif

struct Transform{
    vec2 pos;
    vec2 scale;
    
    unsigned int shaderID;
};
