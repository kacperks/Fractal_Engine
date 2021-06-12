#include "Math.h"

namespace fr {
    struct Vec3 {
        Vec3() {
            x = 0.0f;
            y = 0.0f;
            z = 0.0f;
        }
      
        Vec3(float X, float Y, float Z) {
            x = X;
            y = Y;
            z = Z;
        }
      
        float x, y, z;
    };
}
