#pragma once

#include "Math.h"
#include "Vector3.h"
#include "Vector4.h"

namespace fr::Math {
    class Mat4 {
    private:
        float matrix[4][4];
    public:
        Mat4() {
            SetZero();
        }

        Mat4(float e00, float e01, float e02, float e03,
            float e10, float e11, float e12, float e13,
            float e20, float e21, float e22, float e23,
            float e30, float e31, float e32, float e33) {
            matrix[0][0] = e00; matrix[0][1] = e01; matrix[0][2] = e02; matrix[0][3] = e03;
            matrix[1][0] = e10; matrix[1][1] = e11; matrix[1][2] = e12; matrix[1][3] = e13;
            matrix[2][0] = e20; matrix[2][1] = e21; matrix[2][2] = e22; matrix[2][3] = e23;
            matrix[3][0] = e30; matrix[3][1] = e31; matrix[3][2] = e32; matrix[3][3] = e33;
        }

        Mat4(Vec4& vec) {
            matrix[0][0] = vec.x; matrix[0][1] = vec.y; matrix[0][2] = vec.z; matrix[0][3] = vec.w;
            matrix[1][0] = vec.x; matrix[1][1] = vec.y; matrix[1][2] = vec.z; matrix[1][3] = vec.w;
            matrix[2][0] = vec.x; matrix[2][1] = vec.y; matrix[2][2] = vec.z; matrix[2][3] = vec.w;
            matrix[3][0] = vec.x; matrix[3][1] = vec.y; matrix[3][2] = vec.z; matrix[3][3] = vec.w;
        }

        Mat4(Vec3& pos, Vec3& scale, Vec3& rot) {
            SetZero();

            SetPosition(pos);
            SetScale(scale);
            SetRotX(rot.x);
            SetRotY(rot.y);
            SetRotZ(rot.z);
        }

        void SetZero() {
            matrix[0][0] = 0.0f; matrix[0][1] = 0.0f; matrix[0][2] = 0.0f; matrix[0][3] = 0.0f;
            matrix[1][0] = 0.0f; matrix[1][1] = 0.0f; matrix[1][2] = 0.0f; matrix[1][3] = 0.0f;
            matrix[2][0] = 0.0f; matrix[2][1] = 0.0f; matrix[2][2] = 0.0f; matrix[2][3] = 0.0f;
            matrix[3][0] = 0.0f; matrix[3][1] = 0.0f; matrix[3][2] = 0.0f; matrix[3][3] = 0.0f;
        }

        void SetIdentity() {
            matrix[0][0] = 1.0f;
            matrix[1][1] = 1.0f;
            matrix[2][2] = 1.0f;
            matrix[3][3] = 1.0f;
        }

        void SetPosition(Vec3& pos) {
            matrix[0][3] = pos.x;
            matrix[1][3] = pos.y;
            matrix[2][3] = pos.z;
        }

        void SetScale(Vec3& scale) {
            matrix[0][0] = scale.x;
            matrix[1][1] = scale.y;
            matrix[2][2] = scale.z;
        }

        void SetRotX(float angle) {
            float c = Math::Cos(Math::Radians(angle));
            float s = Math::Sin(Math::Radians(angle));

            matrix[1][1] = c;
            matrix[1][2] = -s;
            matrix[2][1] = s;
            matrix[2][2] = c;
        }

        void SetRotY(float angle) {
            float c = Math::Cos(Math::Radians(angle));
            float s = Math::Sin(Math::Radians(angle));

            matrix[0][0] = c;
            matrix[0][2] = s;
            matrix[2][0] = -s;
            matrix[2][2] = c;
        }

        void SetRotZ(float angle) {
            float c = Math::Cos(Math::Radians(angle));
            float s = Math::Sin(Math::Radians(angle));

            matrix[0][0] = c;
            matrix[0][1] = -s;
            matrix[1][0] = s;
            matrix[1][1] = c;
        }

        void SetOrthographic(float left, float right, float bottom, float top, float n, float f) {
            matrix[0][0] = 2.0f / (right - left);
            matrix[1][1] = 2.0f / (top - bottom);
            matrix[2][2] = 2.0f / (n - f);
            matrix[3][0] = (left + right) / (left - right);
            matrix[3][1] = (bottom + top) / (bottom - top);
            matrix[3][2] = (far + n) / (far - f);
        }

        void SetPerspective(float fov, float aspectRatio, float n, float f) {
            float q = 1.0f / Math::Tan(Math::Radians(0.5f * fov));
            float a = q / aspectRatio;
            float b = (n + f) / (n - f);
            float c = (2.0f * n * f) / (n - f);

            matrix[0][0] = a;
            matrix[1][1] = q;
            matrix[2][2] = b;
            matrix[2][3] = -1.0f;
            matrix[3][2] = c;
        }

        static Mat4 Translate(Vec3& pos) {
            Mat4 mat;
            mat.SetPosition(pos);
            return mat;
        }

        static Mat4 Scale(Vec3& s) {
            Mat4 mat;
            mat.SetScale(s);
            return mat;
        }

        static Mat4 Rotate(Vec3& rot) {
            Mat4 mat;
            mat.SetRotX(rot.x);
            mat.SetRotY(rot.y);
            mat.SetRotZ(rot.z);
            return mat;
        }

        float Get(int x, int y) {
            return matrix[x][y];
        }

        void Set(int x, int y, float val) {
            matrix[x][y] = val;
        }

        Mat4& operator*(Mat4& other) {
            Mat4 mat;
            for (int x = 0; x < 4; ++x) {
                for (int y = 0; y < 4; ++y) {
                    float m = 0.0f;
                    for (int i = 0; i < 4; ++i) {
                        m += matrix[x][i] * other.matrix[i][y];
                    }
                    mat.matrix[x][y] = m;
                }
            }
            return mat;
        }

        Mat4 operator/(Mat4& other) {
            return Mat4(matrix[0][0] / other.matrix[0][0], matrix[0][1] / other.matrix[0][1], matrix[0][2] / other.matrix[0][2], matrix[0][3] / other.matrix[0][3],
                matrix[1][0] / other.matrix[1][0], matrix[1][1] / other.matrix[1][1], matrix[1][2] / other.matrix[1][2], matrix[1][3] / other.matrix[1][3],
                matrix[2][0] / other.matrix[2][0], matrix[2][1] / other.matrix[2][1], matrix[2][2] / other.matrix[2][2], matrix[2][3] / other.matrix[2][3],
                matrix[3][0] / other.matrix[3][0], matrix[3][1] / other.matrix[3][1], matrix[3][2] / other.matrix[3][2], matrix[3][3] / other.matrix[3][3]);
        }

        Mat4 operator+(Mat4& other) {
            return Mat4(matrix[0][0] + other.matrix[0][0], matrix[0][1] + other.matrix[0][1], matrix[0][2] + other.matrix[0][2], matrix[0][3] + other.matrix[0][3],
                matrix[1][0] + other.matrix[1][0], matrix[1][1] + other.matrix[1][1], matrix[1][2] + other.matrix[1][2], matrix[1][3] + other.matrix[1][3],
                matrix[2][0] + other.matrix[2][0], matrix[2][1] + other.matrix[2][1], matrix[2][2] + other.matrix[2][2], matrix[2][3] + other.matrix[2][3],
                matrix[3][0] + other.matrix[3][0], matrix[3][1] + other.matrix[3][1], matrix[3][2] + other.matrix[3][2], matrix[3][3] + other.matrix[3][3]);
        }

        Mat4 operator-(Mat4& other) {
            return Mat4(matrix[0][0] - other.matrix[0][0], matrix[0][1] - other.matrix[0][1], matrix[0][2] - other.matrix[0][2], matrix[0][3] - other.matrix[0][3],
                matrix[1][0] - other.matrix[1][0], matrix[1][1] - other.matrix[1][1], matrix[1][2] - other.matrix[1][2], matrix[1][3] - other.matrix[1][3],
                matrix[2][0] - other.matrix[2][0], matrix[2][1] - other.matrix[2][1], matrix[2][2] - other.matrix[2][2], matrix[2][3] - other.matrix[2][3],
                matrix[3][0] - other.matrix[3][0], matrix[3][1] - other.matrix[3][1], matrix[3][2] - other.matrix[3][2], matrix[3][3] - other.matrix[3][3]);
        }

        Mat4 Mul(Mat4& other) {
            return (*this) * other;
        }

        Mat4 Div(Mat4& other) {
            return (*this) / other;
        }

        Mat4 Add(Mat4& other) {
            return (*this) + other;
        }

        Mat4 Min(Mat4& other) {
            return (*this) - other;
        }
        float* ValuePointer() { return &(matrix[0][0]); }
    };
}