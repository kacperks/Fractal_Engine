#pragma once

#include "Math.h"
#include "Vector3.h"
#include <cmath>

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

        static Mat4& Scale(const Vec3& scale) {
            Mat4 mat = Mat4(1.0f);
            mat.e0 = scale.x;
            mat.e5 = scale.y;
            mat.e10 = scale.z;
            mat.InitArray();
            return mat;
        }
        
        static Mat4& Rotate(float angle, const Vec3& axis) {
            float angleR = angle * Math::PI() / 180;
            float Cos = std::cos(angleR);
            float Sin = std::sin(angleR);
            float omc = 1.0f - Cos;
            
            float ax = axis.x;
            float ay = axis.y;
            float az = axis.z;
            
            Mat4 mat = Mat4(1.0f);  
            mat.e0 = ax * ax * omc + Cos;
            mat.e4 = ay * ax * omc + az * Sin;
            mat.e8 = ax * az * omc - ay * Sin;
            mat.e1 = ax * ay * omc - az * Sin;
	    mat.e5 = ay * ay * omc + Cos;
	    mat.e9 = ay * az * omc + ax * Sin;
	    mat.e2 = ax * az * omc + ay * Sin;
	    mat.e8 = ay * az * omc - ax * Sin;
	    mat.e10 = az * az * omc + Cos;
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
    };
}
