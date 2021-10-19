#include "pch.h"
#include "Vector4.h"
namespace fr {
        Vec4 Vec4::operator+(const Vec4& other) { return Vec4(x + other.x, y + other.y, z + other.z, w + other.w); }
        Vec4 Vec4::operator+(float other) { return Vec4(x + other, y + other, z + other, w + other); }

        Vec4 Vec4::operator-(const Vec4& other) { return Vec4(x - other.x, y - other.y, z - other.z, w - other.w); }


        Vec4 Vec4::operator/(const Vec4& other) { return Vec4(x / other.x, y / other.y, z / other.z, w / other.w); }
        Vec4 Vec4::operator/(float other) { return Vec4(x / other, y / other, z / other, w / other); }

        Vec4 Vec4::operator*(const Vec4& other) {
            return Vec4(x * other.x, y * other.y, z * other.z, w * other.w);
        }

        bool Vec4::operator==(Vec4 other) {
            return x == other.x && y == other.y && z == other.z && w == other.w;
        }

        bool Vec4::operator!=(Vec4 other) {
            return x != other.x && y != other.y && z != other.z && w != other.w;
        }
            
        void Vec4::operator+=(Vec4 other) {
            x += other.x;
            y += other.x;
            z += other.x;
            w += other.x;
        }

        void Vec4::operator-=(Vec4 other) {
            x -= other.x;
            y -= other.x;
            z -= other.x;
            w -= other.x;
        }
            
        void Vec4::operator*=(Vec4 other) {
            x *= other.x;
            y *= other.x;
            z *= other.x;
            w *= other.x;
        }

        void Vec4::operator/=(Vec3 other) {
            x /= other.x;
            y /= other.x;
            z /= other.x;
            w /= other.x;
        }

        float Vec4::Length() { return Math::Sqrt(x*x + y*y + z*z + w*w); }
        Vec4 Vec4::Normalized() { Vec4 v = *this; return v / Length();}
}