#pragma once

#include "../Base/BaseComponent.h"
#include <glm/ext/vector_float3.hpp>

constexpr glm::vec3 AXIS_X(1.0f, 0.0f, 0.0f);
constexpr glm::vec3 AXIS_Y(0.0f, 1.0f, 0.0f);
constexpr glm::vec3 AXIS_Z(0.0f, 0.0f, 1.0f);

struct Transform3D :public ECS::BaseComponent {
	glm::vec3 Scale = glm::vec3(1.0f);
	glm::vec3 Position = glm::vec3(0.0f);
	glm::vec3 Rotation = glm::vec3(0.0f);

	Transform3D(const glm::vec3& position, const glm::vec3& scale, const glm::vec3& rotation) :
		Position(position), Scale(scale), Rotation(rotation) {}

	Transform3D(const glm::vec3& position, const glm::vec3& scale) :
		Position(position), Scale(scale) {}

	Transform3D(const glm::vec3& position) :
		Position(position) {}

	Transform3D() = default;
	~Transform3D() = default;

};

