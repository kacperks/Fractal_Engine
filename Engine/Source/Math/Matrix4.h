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

        static Mat4& Translate(const Vec3& pos);
        static Mat4& Scale(Vec3& scale);
        static Mat4& Rotate(float angle, Vec3& axis);
        static Mat4& Ortho(float left, float right, float bottom, float top, float near1, float far1);

        static Mat4& Perspective(float fov, float aspectRatio, float near1, float far1);
        static Mat4 Mul(Mat4 t, Mat4 other);

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