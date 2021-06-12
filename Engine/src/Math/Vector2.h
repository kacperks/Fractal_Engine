#include "Math.h"

namespace fr {
    struct Vec2 {
        Vec2(): x(0.0f), y(0.0f) {
          
        }
      
        Vec2(float x, float y): x(x), y(y) {
          
        }
      
        Vec2 operator+(const Vec2& other) {
            return Vec2(x + other.x, y + other.y); 
        }
      
        Vec2 operator-(const Vec2& other) {
            return Vec2(x - other.x, y - other.y); 
        }
      
        Vec2 operator/(const Vec2& other) {
            return Vec2(x / other.x, y / other.y); 
        }
      
        Vec2 operator*(const Vec2& other) {
            return Vec2(x * other.x, y * other.y); 
        }
      
        float x, y;
    };
}
