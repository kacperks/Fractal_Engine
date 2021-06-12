#include "Math.h"

namespace fr{
    struct Matrix4{
        Matrix4(float diagonal):
            e0(diagonal), e1(0.0f), e2(0.0f), e3(0.0f), e4(0.0f), e5(diagonal),
            e6(0.0f), e7(0.0f), e8(0.0f), e9(0.0f), e10(diagonal),
            e11(0.0f), e12(0.0f), e13(0.0f), e14(0.0f), e15(diagonal) {
            
        }
        
        Matrix4& Identity(){
            return Matrix4(1.0f);
        }
        
        float e0, e1, e2, e3, e4, e5, e6, e7, e8, e9, e10, e11, e12, e13, 14, 15;
        
        float* ToPtr(){
            float* matrix = { e0, e1, e2, e3, e4, e5, e6, e7, e8, e9, e10, e11, e12, e13, e14, e15; }
            return matrix;
        }
    };
}
