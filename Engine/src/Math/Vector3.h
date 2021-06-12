#pragma once

#include "Math.h"

namespace fr {
    struct Vec3 {
        Vec3(): x(0.0f), y(0.0f), z(0.0f) {
            
        }

        Vec3(float x, float y, float z): x(x), y(y), z(z) {
            
        }

        Vec3 operator+(const Vec3& other) {
            return Vec3(x + other.x, y + other.y, z + other.z);
        }

        Vec3 operator-(const Vec3& other) {
            return Vec3(x - other.x, y - other.y, z - other.z);
        }

        Vec3 operator/(const Vec3& other) {
            return Vec3(x / other.x, y / other.y, z / other.z);
        }

        Vec3 operator*(const Vec3& other) {
            return Vec3(x * other.x, y * other.y, z * other.z);
        }

        float x, y, z;
    };
}
