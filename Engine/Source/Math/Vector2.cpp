#include "pch.h"
#include "Vector2.h"

namespace fr {
        Vec2 Vec2::operator+(const Vec2& other) { return Vec2(x + other.x, y); }
        Vec2 Vec2::operator-(const Vec2& other) { return Vec2(x - other.x, y); }
        Vec2 Vec2::operator/(const Vec2& other) { return Vec2(x / other.x, y); }
        Vec2 Vec2::operator*(const Vec2& other) { return Vec2(x * other.x, y); }
        float Vec2::Lenght() { return Math::Sqrt(x * x + y * y); }
}