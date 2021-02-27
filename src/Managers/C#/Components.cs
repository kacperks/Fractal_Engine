using System.Collections.Generic;
using System;

namespace Components
{
    public class Component{
        public struct Vector3{
            float x, y, z;
        };
        public struct Transform{
            string entity;
            Vector3 position;
            Vector3 rotation;
            Vector3 scale;
        };
    }
}
