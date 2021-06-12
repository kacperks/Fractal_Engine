#pragma once

#include "Math.h"
#include "Vector3.h"

namespace fr {
    struct Mat4 {
        Mat4(float diagonal) :
            e0(diagonal), e1(0.0f), e2(0.0f), e3(0.0f), e4(0.0f), e5(diagonal),
            e6(0.0f), e7(0.0f), e8(0.0f), e9(0.0f), e10(diagonal),
            e11(0.0f), e12(0.0f), e13(0.0f), e14(0.0f), e15(diagonal), created(true) {
            InitArray();
        }
        
        static void Translate(const Mat4& other, const Vec3& pos) {
            if(!other.created)return;
            other.e12 = pos.x;
            other.e13 = pos.y;
            other.e14 = pos.z;
            other.InitArray();
        }
        
        static void Scale(const Mat4& other, const Vec3& scale) {
            if(!other.created)return;
            other.e0 = scale.x;
            other.e5 = scale.y;
            other.e10 = scale.z;
            other.InitArray();
        }
        
        float e0, e1, e2, e3, e4, e5, e6, e7, e8, e9, e10, e11, e12, e13, e14, e15;
        float matrix[16];
        bool created = false;
        
        void InitArray(){
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
