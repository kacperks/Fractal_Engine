#pragma once

#ifndef FR_MATH_VEC3
#define FR_MATH_VEC3

#include "Math.h"

#include "Vector.h"

namespace fr {
        class Vec3 : public Vector<float, 3> {
        public:
            Vec3() : x(0.0f), y(0.0f), z(0.0f) {}
            Vec3(float x, float y, float z) : x(x), y(y), z(z) {}

            inline Vec3 Normalized();
            inline float Lenght();

            Vec3 operator+(const Vec3& other);
            Vec3 operator+(float other);

            Vec3 operator-(const Vec3& other);
            Vec3 operator-(float other);

            Vec3 operator/(const Vec3& other);
            Vec3 operator/(float other);

            Vec3 operator*(const Vec3& other);
            Vec3 operator*(float other);

            bool operator==(Vec3 other);
            bool operator!=(Vec3 other);

            void operator+=(Vec3 other);
            void operator-=(Vec3 other);

            void operator*=(Vec3 other);
            void operator/=(Vec3 other);

            float x, y, z;
        };
}

#endif