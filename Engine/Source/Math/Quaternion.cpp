#include "pch.h"
#include "Quaternion.h"

namespace fr {
    Quaternion::Quaternion(float x, float y, float z, float w) {
        (*this).x = x;
        (*this).y = y;
        (*this).z = z;
        (*this).w = w;
    }

    Quaternion::Quaternion(Vec4& m) {
        (*this).x = m.x;
        (*this).y = m.y;
        (*this).z = m.z;
        (*this).w = m.w;
    }

    Quaternion::Quaternion(Vec3& axis, float angle) {
        float HalfSin = Math::Sin(angle / 2);
        float HalfCos = Math::Cos(angle / 2);

        (*this).x = axis.x * HalfSin;
        (*this).y = axis.y * HalfSin;
        (*this).z = axis.z * HalfSin;
        (*this).w = HalfCos;
    }

    Quaternion::Quaternion(Mat4& m) {
        // not yet ok?
    }
}