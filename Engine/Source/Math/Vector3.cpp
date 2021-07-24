#include "pch.h"
#include "Vector3.h"

namespace fr {
    Vec3 Vec3::operator+(const Vec3& other) { return Vec3(x + other.x, y + other.y, z + other.z); }
    Vec3 Vec3::operator-(const Vec3& other) { return Vec3(x - other.x, y - other.y, z - other.z); }
    Vec3 Vec3::operator/(const Vec3& other) { return Vec3(x / other.x, y / other.y, z / other.z); }
    Vec3 Vec3::operator*(const Vec3& other) { return Vec3(x * other.x, y * other.y, z * other.z); }
    float Vec3::lenght() { return Math::Sqrt(x * x + y * y + z * z); }
}