#pragma once

struct Vec2{
    float x;
    float y;

    Vec2 operator * (float scalar){
        return {
            x * scalar,
            y * scalar
        };
    }

    Vec2 operator + (Vec2 vec){
        return{
            x + vec.x,
            y + vec.y
        };
    }

    Vec2 operator - (Vec2 vec){
        return{
            vec.x - x,
            vec.y - y
        };
    }
};

struct IVec2{
    int x;
    int y;

    IVec2 operator + (IVec2 vec){
        return{
            x + vec.x,
            y + vec.y
        };
    }

    IVec2 operator - (IVec2 vec){
        return{
            vec.x - x,
            vec.y - y
        };
    }
};
