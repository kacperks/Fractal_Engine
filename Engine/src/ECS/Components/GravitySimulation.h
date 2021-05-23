#pragma once

#include "pch.h"
#include "ECS/Base/BaseComponent.h"

struct Gravity : public ECS::BaseComponent {
	Gravity() = default;
	~Gravity() = default;

	float Mass;
	float Radius;
	float GravitionalConstant;

	glm::vec3 InitialVelocity;
	glm::vec3 CurrentVelocity;
};
