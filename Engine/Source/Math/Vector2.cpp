#include "pch.h"
#include "Vector2.h"

namespace fr {
    Vec2 Vec2::operator+(const Vec2& other) { return Vec2(x + other.x, y); }
    Vec2 Vec2::operator-(const Vec2& other) { return Vec2(x - other.x, y); }
    Vec2 Vec2::operator/(const Vec2& other) { return Vec2(x / other.x, y); }
    Vec2 Vec2::operator*(const Vec2& other) { return Vec2(x * other.x, y); }
    float Vec2::lenght() { return Math::SQRT(x * x + y * y); }
}