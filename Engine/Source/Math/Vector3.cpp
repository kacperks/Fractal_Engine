#include "pch.h"
#include "Vector3.h"

namespace fr {
        Vec3 Vec3::operator+(const Vec3& other) { return Vec3(x + other.x, y + other.y, z + other.z); }
        Vec3 Vec3::operator-(const Vec3& other) { return Vec3(x - other.x, y - other.y, z - other.z); }
        Vec3 Vec3::operator/(const Vec3& other) { return Vec3(x / other.x, y / other.y, z / other.z); }
        Vec3 Vec3::operator*(const Vec3& other) { return Vec3(x * other.x, y * other.y, z * other.z); }
        void Vec3::operator+=(Vec3 other) { x += other.x; y += other.y; z += other.z; }
        Vec3 Vec3::operator*(float other) { return Vec3(x * other, y * other, z * other); }
        Vec3 Vec3::operator/(float other) { return Vec3(x / other, y / other, z / other); }
        float Vec3::Lenght() { return Math::Sqrt(x * x + y * y + z * z); }
}