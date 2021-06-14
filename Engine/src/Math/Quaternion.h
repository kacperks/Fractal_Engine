#pragma once

#include "pch.h"
#include "Math.h"
#include "Vector4.h"

namespace fr {
    struct Quaternion {
        Quaternion() : xyzw({ 0.0f, 0.0f, 0.0f, 0.0f }) { }
        Quaternion(Vec4& xyzw) : xyzw(xyzw) { }

        Quaternion operator=(Vec4& other) {
            xyzw = other;
            return *this;
        }

        Quaternion operator+(Quaternion& other) {
            Vec4 a = xyzw + other.xyzw;
            return Quaternion(a);
        }

        Quaternion operator-(Quaternion& other) {
            Vec4 a = xyzw - other.xyzw;
            return Quaternion(a);
        }

        Quaternion operator*(Quaternion& other) {
            Vec4 a = xyzw * other.xyzw;
            return Quaternion(a);
        }

        Quaternion operator/(Quaternion& other) {
            Vec4 a = xyzw / other.xyzw;
            return Quaternion(a);
        }

        Vec4 xyzw;
    };
}