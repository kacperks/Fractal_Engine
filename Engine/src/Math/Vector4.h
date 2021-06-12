#include "Math.h"

namespace fr {
    struct Vec4 {
        Vec4(): x(0.0f), y(0.0f), z(0.0f), w(0.0f) {
           
        }
      
        Vec4(float x, float y, float z, float w): x(x), y(y), z(z), w(w) {
          
        }
        
        Vec4 operator+(const Vec4& other) {
            return Vec4(x + other.x, y + other.y, z + other.z, w + other.w);
        }
      
        Vec4 operator-(const Vec4& other) {
            return Vec4(x - other.x, y - other.y, z - other.z, w - other.w);
        }
      
        Vec4 operator/(const Vec4& other) {
            return Vec4(x / other.x, y / other.y, z / other.z, w / other.w);
        }
      
        Vec4 operator*(const Vec4& other) {
            return Vec4(x * other.x, y * other.y, z * other.z, w * other.w);
        }
      
        float x, y, z, w;
    };
}
