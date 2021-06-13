#include "pch.h"
#include "Math.h"
#include "Vector4.h"

namespace fr {
    struct Quaternion {
        Quaternion(): xyzw({ 0.0f, 0.0f, 0.0f, 0.0f }) { }
        Quaternion(Vec4& xyzw): xyzw(xyzw) { }

        Quaternion operator=(Vec4& other) {
            xyzw = other;
            return *this;
        }

        Quaternion operator+(Quaternion& other) {
            return Quaternion(xyzw + other.xyzw);   
        }

        Quaternion operator-(Quaternion& other) {
            return Quaternion(xyzw - other.xyzw);   
        }

        Quaternion operator*(Quaternion& other) {
            return Quaternion(xyzw * other.xyzw);   
        }

        Quaternion operator/(Quaternion& other) {
            return Quaternion(xyzw / other.xyzw);   
        }
        
        Vec4 xyzw;
    };
}
