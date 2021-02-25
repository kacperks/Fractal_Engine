#pragma once

#include "../../fractal.hpp"

namespace fr{
    class tr{
    public:
        struct Vector3{
                float x;
                float y;
                float z;
        };
        struct Transform{
                string name;
                Vector3 Position;
                Vector3 Rotation;
                Vector3 Scale;
        };
    };
};