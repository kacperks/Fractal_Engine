#include "pch.h"
#include "Vector2.h"

namespace fr {
    Vec2 Vec2::operator+(const Vec2& other) { return Vec2(x + other.x, y); }
    Vec2 Vec2::operator-(const Vec2& other) { return Vec2(x - other.x, y); }
    Vec2 Vec2::operator/(const Vec2& other) { return Vec2(x / other.x, y); }
    Vec2 Vec2::operator*(const Vec2& other) { return Vec2(x * other.x, y); }
    void Vec2::operator+=(Vec2 other) { x += other.x; y += other.y; }
    Vec2 Vec2::operator*(float other) { return Vec2(x * other, y * other); }
    Vec2 Vec2::operator/(float other) { return Vec2(x / other, y / other); }
    float Vec2::Length() { return Math::Sqrt(x * x + y * y); }
}