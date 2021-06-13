#include "pch.h"
#include "Math.h"
#include "Vector3.h"

namespace fr {
    struct Quaternion {
        Quaternion(): x(0.0f), y(0.0f), z(0.0f), w(0.0f) { }
        Quaternion(float x, float y, float z, float w): x(x), y(y), z(z), w(w) { }
        
        float Length() { return (float)std::sqrt(x * x, y * y, z * z, w * w); }
      
        void Normalize() {
            float l = Length();
            x /= l;
            y /= l;
            z /= l;
            w /= l;
        }
      
        float x, y, z, w;
    };
}
