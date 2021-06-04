#pragma once

#include "pch.h"

namespace fr {
	using matrix3 = glm::mat3;
	using vector3i = glm::ivec3;
	using vector4i = glm::ivec4;
	using vector2u = glm::uvec2;
	using vector3u = glm::uvec3;
	using vector4u = glm::uvec4;
	using vector2f = glm::fvec2;
	using vector3f = glm::fvec3;
	using vector4f = glm::fvec4;
	using vector2i = glm::ivec2;
	using matrix4 = glm::mat4;
	using quaternion = glm::quat;

	double Sin(double angle) { return glm::sin(angle); }
	double Cos(double angle) { return glm::cos(angle); }
	double Tan(double angle) { return glm::tan(angle); }


	float Radians(float angle) { return glm::radians(angle); }
	vector3f Radians2(const vector3f& v) { return glm::radians(v); }
	vector3f Degrees(const vector3f& v) { return glm::degrees(v); }
}