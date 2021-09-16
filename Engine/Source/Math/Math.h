#pragma once

#include "pch.h"
#include "Vector2.h"
#include "Vector3.h"
#include "Vector4.h"

namespace fr::Math {
	inline static float Cos(int deg);
	inline static float Sin(int deg);
	inline static float Tan(int deg);
	inline static float CoTan(int deg);
	inline static float Lerp(float start, float stop, float step);
	inline static float PI();

	inline static float Radians(float degrees);
	inline static float Degrees(float radians);

	inline static float Sqrt(float num);
	inline static float Q_rsqrt(float num);

	inline static float power(float base, int exp);
	inline static int fact(int n);

	inline static float RandomRange(float min, float max);

	inline static float Abs(float num);
	inline static float Abs(int num);
}