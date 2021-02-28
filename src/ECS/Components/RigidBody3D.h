#pragma once
#include <GLM/ext/vector_float3.hpp>
#include "ECS/Core/BaseComponent.h"

static const glm::vec3 GRAVITY(0.0f, -10.0f, 0.0f);

struct RigidBody3D : public ECS::BaseComponent {
	RigidBody3D() = default;
	~RigidBody3D() = default;

	float Speed = 0.5f;
	float Masse = 1.0f;
	float GravityScale = 1.0f;
	glm::vec3 Accelaration = glm::vec3(0.0f);
	glm::vec3 Velocity = glm::vec3(0.0f, 1.0f, 0.0f);
};