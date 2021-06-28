#pragma once

#ifndef FR_MATRIX_4
#define FR_MATRIX_4

#include "Math.h"
#include "Vector3.h"
#include "Vector4.h"

namespace fr {

    struct Mat4 {
        Mat4(float diagonal) :
            e0(diagonal), e1(0.0f), e2(0.0f), e3(0.0f), e4(0.0f), e5(diagonal),
            e6(0.0f), e7(0.0f), e8(0.0f), e9(0.0f), e10(diagonal),
            e11(0.0f), e12(0.0f), e13(0.0f), e14(0.0f), e15(diagonal) {
            InitArray();
        }

        static Mat4& Translate(const Vec3& pos) {
            Mat4 mat = Mat4(1.0f);
            mat.e12 = pos.x;
            mat.e13 = pos.y;
            mat.e14 = pos.z;
            mat.InitArray();
            return mat;
        }

        static Mat4& Scale(Vec3& scale) {
            Mat4 mat = Mat4(1.0f);
            mat.e0 = scale.x;
            mat.e5 = scale.y;
            mat.e10 = scale.z;
            mat.InitArray();
            return mat;
        }

        static Mat4& Rotate(float angle, Vec3& axis) {

            float angleR = angle * Math::PI() / 180.0;
            float cos = Math::Cos(angleR);
            float Sin = Math::Sine(angleR);
            float omc = 1.0f - cos;

            float ax = axis.x;
            float ay = axis.y;
            float az = axis.z;

            Mat4 mat = Mat4(1.0f);
            mat.e0 = ax * ax * omc + cos;
            mat.e4 = ay * ax * omc + az * Sin;
            mat.e8 = ax * az * omc - ay * Sin;
            mat.e1 = ax * ay * omc - az * Sin;
            mat.e5 = ay * ay * omc + cos;
            mat.e9 = ay * az * omc + ax * Sin;
            mat.e2 = ax * az * omc + ay * Sin;
            mat.e8 = ay * az * omc - ax * Sin;
            mat.e10 = az * az * omc + cos;
            mat.InitArray();
            return mat;

        }

        static Mat4& Ortho(float left, float right, float bottom, float top, float near1, float far1) {
            Mat4 mat = Mat4(1.0f);
            mat.e0 = 2.0f / (right - left);
            mat.e5 = 2.0f / (top - bottom);
            mat.e10 = 2.0f / (near1 - far1);
            mat.e3 = (left + right) / (left - right);
            mat.e7 = (bottom + top) / (bottom - top);
            mat.e11 = (far1 + near1) / (far1 - near1);
            mat.InitArray();
            return mat;
        }

        static Mat4& Perspective(float fov, float aspectRatio, float near1, float far1) {
            float r = 0.5f * fov * 3.14159265359 / 180.0f;
            float q = 1.0f / std::tan(r);
            float a = q / aspectRatio;
            float b = (near1 + far1) / (near1 - far1);
            float c = (2.0f * near1 * far1 / (near1 - far1));

            Mat4 mat = Mat4(1.0f);
            mat.e0 = a;
            mat.e5 = q;
            mat.e10 = b;
            mat.e14 = -1.0f;
            mat.e11 = c;
            mat.InitArray();
            return mat;
        }


        static Mat4& Mul(Mat4& t, Mat4& other) {
            Mat4& mat = Mat4(1.0f);
            float sum = 0.0f;
            for (int x = 0; x < 4; x++) {
                for (int y = 0; y < 4; y++) {
                    for (int i = 0; i < 4; i++) {
                        sum += t.matrix[x + i * 4] * other.matrix[i + y * 4];
                    }
                }
            }
            mat.e0 = sum;
            mat.e1 = sum;
            mat.e2 = sum;
            mat.e3 = sum;
            mat.e4 = sum;
            mat.e5 = sum;
            mat.e6 = sum;
            mat.e7 = sum;
            mat.e8 = sum;
            mat.e9 = sum;
            mat.e10 = sum;
            mat.e11 = sum;
            mat.e12 = sum;
            mat.e13 = sum;
            mat.e14 = sum;
            mat.e15 = sum;
            mat.InitArray();
            return mat;
        }

        float e0, e1, e2, e3, e4, e5, e6, e7, e8, e9, e10, e11, e12, e13, e14, e15;
        float matrix[16];
        void InitArray() {
            matrix[0] = e0;
            matrix[1] = e1;
            matrix[2] = e2;
            matrix[3] = e3;
            matrix[4] = e4;
            matrix[5] = e5;
            matrix[6] = e6;
            matrix[7] = e7;
            matrix[8] = e8;
            matrix[9] = e9;
            matrix[10] = e10;
            matrix[11] = e11;
            matrix[12] = e12;
            matrix[13] = e13;
            matrix[14] = e14;
            matrix[15] = e15;
        }

        Mat4 operator=(Vec4 vecs[4]) {
            e0 = vecs[0].x; e1 = vecs[0].y; e2 = vecs[0].z; e3 = vecs[0].w;
            e4 = vecs[1].x; e5 = vecs[1].y; e6 = vecs[1].z; e7 = vecs[1].w;
            e8 = vecs[2].x; e9 = vecs[2].y; e10 = vecs[2].z; e11 = vecs[2].w;
            e12 = vecs[3].x; e13 = vecs[3].y; e14 = vecs[3].z; e15 = vecs[3].w;
        }

    };
}

#endif