
#ifndef FR_VECTORS
#define FR_VECTORS

namespace fr {
    template<size_t Size, typename T>
    class Vector;
  
    template<typename T>
    class Vector<2, T> {
        Vector<2, T>() : x((T)0), y((T)0) { }
        Vector<2, T>(T x, T y) : x(x), y(y) { }
      
        Vector<2, T>& operator*(const Vector<2, T>& other) { return Vector<2, T>(x * other.x, y * other.y); }
        Vector<2, T>& operator/(const Vector<2, T>& other) { return Vector<2, T>(x / other.x, y / other.y); }
        Vector<2, T>& operator+(const Vector<2, T>& other) { return Vector<2, T>(x + other.x, y + other.y); }
        Vector<2, T>& operator-(const Vector<2, T>& other) { return Vector<2, T>(x - other.x, y - other.y); }
      
        T x, y;
    }
    
    using Vector2f = Vector<2, float>;
    using Vector2d = Vector<2, double>;
    using Vector2i = Vector<2, int>;
    using Vector2l = Vector<2, long>;
  
    template<typename T>
    class Vector<3, T> {
        Vector<3, T>() : x((T)0), y((T)0), z((T)0) { }
        Vector<3, T>(T x, T y, T z) : x(x), y(y), z(z) { }
      
        Vector<3, T>& operator*(const Vector<3, T>& other) { return Vector<3, T>(x * other.x, y * other.y, z * other.z); }
        Vector<3, T>& operator/(const Vector<3, T>& other) { return Vector<3, T>(x / other.x, y / other.y, z / other.z); }
        Vector<3, T>& operator+(const Vector<3, T>& other) { return Vector<3, T>(x + other.x, y + other.y, z + other.z); }
        Vector<3, T>& operator-(const Vector<3, T>& other) { return Vector<3, T>(x - other.x, y - other.y, z - other.z); }
      
        T x, y, z;
    }
  
    using Vector3f = Vector<3, float>;
    using Vector3d = Vector<3, double>;
    using Vector3i = Vector<3, int>;
    using Vector3l = Vector<3, long>;
    
    template<typename T>
    class Vector<4, T> {
        Vector<4, T>() : x((T)0), y((T)0), z((T)0), w((T)0) { }
        Vector<4, T>(T x, T y, T z, T w) : x(x), y(y), z(z), w(w) { }
      
        Vector<4, T>& operator*(const Vector<4, T>& other) { return Vector<4, T>(x * other.x, y * other.y, z * other.x, w * other.w); }
        Vector<4, T>& operator/(const Vector<4, T>& other) { return Vector<4, T>(x / other.x, y / other.y, z / other.x, w / other.w); }
        Vector<4, T>& operator+(const Vector<4, T>& other) { return Vector<4, T>(x + other.x, y + other.y, z + other.x, w + other.w); }
        Vector<4, T>& operator-(const Vector<4, T>& other) { return Vector<4, T>(x - other.x, y - other.y, z - other.x, w - other.w); }

        T x, y, z, w;
    }
    
    using Vector4f = Vector<4, float>;
    using Vector4d = Vector<4, double>;
    using Vector4i = Vector<4, int>;
    using Vector4l = Vector<4, long>;
}

#endif
