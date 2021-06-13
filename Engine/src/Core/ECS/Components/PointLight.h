#pragma once

#include "Core/ECS/Base/BaseComponent.h"

struct PointLight : public ECS::BaseComponent {
	PointLight() = default;
	~PointLight() = default;

	GLfloat Intensity = 1.0f;
	glm::vec3 Color = glm::vec3(1.0f);
};




