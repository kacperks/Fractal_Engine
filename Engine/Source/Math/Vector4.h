#pragma once

#include "Math.h"
#include "Vector.h"

namespace fr {
        class Vec4 : public Vector<float, 4>{
        public:
            Vec4() : x(0.0f), y(0.0f), z(0.0f), w(0.0f) { }
            Vec4(float x, float y, float z, float w) : x(x), y(y), z(z), w(w) { }

            Vec4 operator+(Vec4& other);
            Vec4 operator-(Vec4& other);
            Vec4 operator/(Vec4& other);
            Vec4 operator*(Vec4& other);

            float x, y, z, w;
        };
}