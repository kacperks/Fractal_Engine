#include "pch.h"
#include "Math.h"
#include "Vector3.h"

namespace fr {
    struct Quaternion {
        Quaternion(): x(0.0f), y(0.0f), z(0.0f), w(0.0f) { }
        Quaternion(float x, float y, float z, float w): x(x), y(y), z(z), w(w) { }
        
        Quaternion operator=(Vec3& other) {
            x = other.x;
            y = other.y;
            z = other.z;
            w = 0.0f;
            return *this;
        }
        
        Quaternion operator+(Quaternion& other) {
            return Quaternion(x + other.x, y + other.y, z + other.z, w + other.w);   
        }
        
        Quaternion operator-(Quaternion& other) {
            return Quaternion(x - other.x, y - other.y, z - other.z, w - other.w);   
        }
        
        Quaternion operator*(Quaternion& other) {
            return Quaternion(x * other.x, y * other.y, z * other.z, w * other.w);   
        }
        
        Quaternion operator/(Quaternion& other) {
            return Quaternion(x / other.x, y / other.y, z / other.z, w / other.w);   
        }
      
        float x, y, z, w;
    };
}
