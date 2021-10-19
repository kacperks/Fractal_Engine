#pragma once

#include "Math.h"
#include "Vector.h"

namespace fr {
        class Vec4 : public Vector<float, 4>{
        public:
            Vec4() : x(0.0f), y(0.0f), z(0.0f), w(0.0f) { }
            Vec4(float x, float y, float z, float w) : x(x), y(y), z(z), w(w) { }
            Vec4(float number) : x(number), y(number), z(number), w(number) { }

            inline Vec4 Normalized();
            inline float Length();

            Vec4 operator+(const Vec4& other);
            Vec4 operator+(float other);

            Vec4 operator-(const Vec4& other);
            Vec4 operator-(float other);

            Vec4 operator/(const Vec4& other);
            Vec4 operator/(float other);

            Vec4 operator*(const Vec4& other);
            Vec4 operator*(float other);

            bool operator==(Vec4 other);
            bool operator!=(Vec4 other);

            void operator+=(Vec4 other);
            void operator-=(Vec4 other);

            void operator*=(Vec4 other);
            void operator/=(Vec3 other);

            float x, y, z, w;
        };
}