#include "pch.h"
#include "Vector4.h"

namespace fr {
        Vec4 Vec4::operator+(const Vec4& other) {
            return Vec4(x + other.x, y + other.y, z + other.z, w + other.w);
        }

        Vec4 Vec4::operator-(const Vec4& other) {
            return Vec4(x - other.x, y - other.y, z - other.z, w - other.w);
        }

        Vec4 Vec4::operator/(const Vec4& other) {
            return Vec4(x / other.x, y / other.y, z / other.z, w / other.w);
        }

        Vec4 Vec4::operator*(const Vec4& other) {
            return Vec4(x * other.x, y * other.y, z * other.z, w * other.w);
        }
}