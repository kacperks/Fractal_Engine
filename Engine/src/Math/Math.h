
#pragma once

#ifndef FR_MATH_H
#define FR_MATH_H

#include "pch.h"

#include "Vector3.h"

namespace fr {
	using Matrix3 = glm::mat3;
	using Vector3i = glm::ivec3;
	using Vector4i = glm::ivec4;
	using Vector2u = glm::uvec2;
	using Vector3u = glm::uvec3;
	using Vector4u = glm::uvec4;
	using Vector2f = glm::fvec2;
	using Vector3f = glm::fvec3;
	using Vector4f = glm::fvec4;
	using Vector2i = glm::ivec2;
	using Matrix4 = glm::mat4;
	using Quaternion = glm::quat;
}

namespace fr {
	class Math {
		public:
			static float Cos(int deg);
			static float Sin(int deg);
			static float Lerp(float start, float stop, float step);
			static float PI();

			static float Radians(float degrees);
			static float Degrees(float radians);

			static float power(float base, int exp);
			static int fact(int n);
	};
}

#endif