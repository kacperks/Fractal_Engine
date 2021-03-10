#pragma once

#include "ECS/Base/BaseComponent.h"

constexpr glm::vec3 GRAVITY(0.0f, -9.81f, 0.0f);

struct RigidBody : public ECS::BaseComponent {
	RigidBody() = default;
	~RigidBody() = default;

	GLfloat Mass = 1.0f;
	GLfloat GravityScale = 1.0f;
	glm::vec3 Drag = glm::vec3(0.0f);
	glm::vec3 Force = glm::vec3(0.0f);
	glm::vec3 Velocity = glm::vec3(0.0f);
};
