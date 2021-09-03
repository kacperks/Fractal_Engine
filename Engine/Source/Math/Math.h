#pragma once

#ifndef FR_MATH_H
#define FR_MATH_H

#include "pch.h"
#include "Vector2.h"
#include "Vector3.h"
#include "Vector4.h"

namespace fr {
	class Math {
	public:
		static float Cos(int deg);
		static float Sin(int deg);
		static float Tan(int deg);
		static float CoTan(int deg);
		static float Lerp(float start, float stop, float step);
		static float PI();

		static float Radians(float degrees);
		static float Degrees(float radians);

		static float Sqrt(float num);
		static float Q_rsqrt(float num);

		static float power(float base, int exp);
		static int fact(int n);

		static float RandomRange(float min, float max);

		static float abs(float num);
		static float abs(int num);
	};
}

#endif
