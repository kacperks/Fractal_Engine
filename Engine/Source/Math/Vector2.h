#pragma once

#ifndef FR_MATH_VEC2
#define FR_MATH_VEC2

#include "Math.h"
#include "Vector.h"

namespace fr {
    class Vec2 : public Vector<float, 2> {
    public:
        Vec2() : x(0.0f), y(0.0f) {}
        Vec2(float x, float y) : x(x), y(y) {}
        Vec2(float number) : x(number), y(number) {}

        inline Vec2 Normalized();
        inline float Length();

        Vec2 operator+(const Vec2& other);
        Vec2 operator+(float other);

        Vec2 operator-(const Vec2& other);
        Vec2 operator-(float other);

        Vec2 operator/(const Vec2& other);
        Vec2 operator/(float other);

        Vec2 operator*(const Vec2& other);
        Vec2 operator*(float other);

        bool operator==(Vec2 other);
        bool operator!=(Vec2 other);

        void operator+=(Vec2 other);
        void operator-=(Vec2 other);

        void operator*=(Vec2 other);
        void operator/=(Vec2 other);

        float x, y;
    };
}

#endif