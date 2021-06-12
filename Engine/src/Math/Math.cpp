#include "pch.h"

#include "Math.h"

namespace fr {
	float Math::Radians(float degrees) { return degrees * static_cast<float>(0.01745329251994329576923690768489); }

	float Math::Lerp(float start, float stop, float step) { float v = start; while (v != stop) { v = (stop * step) + (start * 1.0 - step); } return v;}

	float Math::PI() { return 3.14159265359; }

	float Math::Sine(int deg) {
		deg %= 360;
		float rad = deg * PI() / 180;
		float sin = 0;
		for (int i = 0; i < TERMS; i++) {
			sin += power(-1, i) * power(rad, 2 * i + 1) / fact(2 * i + 1);
		}
		return sin;
	}

	float Math::Cos(int deg) {
		deg %= 360; // make it less than 360
		float rad = deg * PI() / 180;
		float cos = 0;

		int i;
		for (i = 0; i < TERMS; i++) {
			cos += power(-1, i) * power(rad, 2 * i) / fact(2 * i);
		}
		return cos;
	}

	float Math::power(float base, int exp) {
		if (exp < 0) {
			if (base == 0)
				return -0;
			return 1 / (base * power(base, (-exp) - 1));
		}
		if (exp == 0)
			return 1;
		if (exp == 1)
			return base;
		return base * power(base, exp - 1);
	}

	int Math::fact(int n) {
		return n <= 0 ? 1 : n * fact(n - 1);
	}
}