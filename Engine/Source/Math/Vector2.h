#pragma once

#ifndef FR_MATH_VEC2
#define FR_MATH_VEC2

#include "Math.h"

namespace fr {
    class Vec2 {
    public:
        Vec2() : x(0.0f), y(0.0f) {}
        Vec2(float x, float y) : x(x), y(y) {}

        inline float lenght();

        Vec2 operator+(const Vec2& other);
        Vec2 operator-(const Vec2& other);
        Vec2 operator/(const Vec2& other);
        Vec2 operator*(const Vec2& other);

        float x, y;
    };
}

#endif