#pragma once

#include "pch.h"
#include "ECS/Base/BaseComponent.h"

struct Vector3 {
	float X;
	float Y;
	float Z;
};

struct Gravity : public ECS::BaseComponent {
	Gravity() = default;
	~Gravity() = default;

	float Mass;
	float Radius;

	glm::vec3 InitialVelocity;
	glm::vec3 CurrentVelocity;
};
