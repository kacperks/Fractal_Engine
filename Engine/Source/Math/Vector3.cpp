#include "pch.h"
#include "Vector3.h"

namespace fr::Math {
        Vec3 Vec3::operator+(const Vec3& other) { return Vec3(x + other.x, y + other.y, z + other.z); }
        Vec3 Vec3::operator-(const Vec3& other) { return Vec3(x - other.x, y - other.y, z - other.z); }
        Vec3 Vec3::operator/(const Vec3& other) { return Vec3(x / other.x, y / other.y, z / other.z); }
        Vec3 Vec3::operator*(const Vec3& other) { return Vec3(x * other.x, y * other.y, z * other.z); }
        void Vec3::operator+=(Vec3 other) { x += other.x; y += other.y; z += other.z; }
        Vec3 Vec3::operator*(float other) { return Vec3(x * other, y * other, z * other); }
        Vec3 Vec3::operator/(float other) { return Vec3(x / other, y / other, z / other); }
        void Vec3::operator=(glm::fvec3 other) { x = other.x; y = other.y; z = other.z; }
        void Vec3::operator/=(float other) { x /= other; y / other; z /= other; }
        float Vec3::Lenght() { return Math::Sqrt(x * x + y * y + z * z); }
        Vec3 Vec3::Normalized() {
            Vec3 vec = *this; float n_length = Lenght();
            return vec / n_length;
        }
        float Vec3::Max(){
            float maxV = x;
            if (x > maxV)
                maxV = x;
            if (y > maxV)
                maxV = y;
           if (z > maxV)
                maxV = z;

            return maxV;
        }

        Vec3 Vec3::Max(Vec3 v) {
            Vec3 r;

            for (int i = 0; i < 3; i++) {
                if (i == 0)
                    r.x = this->x > v.x ? this->x : v.x;
                if (i == 1)
                    r.y = this->y > v.y ? this->y : v.y;
                if (i == 2)
                    r.z = this->z > v.z ? this->z : v.z;
            }

            return r;
        }
}