#include "../../fractal.hpp"

namespace fr{
    class tr{
    public:
        struct Vector3{
            public float x, y, z;
        };
        struct Transform : public ECS::BaseComponent{
            public Vector3 position;
            public Vector3 rotation;
            public Vector3 scale;
        };
    }

};