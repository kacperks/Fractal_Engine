#pragma once

#include "pch.h"

struct DirectionalLight : public ECS::BaseComponent {
	DirectionalLight() = default;
	~DirectionalLight() = default;
	GLfloat Intensity = 1.0f;
	glm::vec3 Color = glm::vec3(1.0f);
	glm::vec3 Direction = glm::vec3(0.0f, 0.0f, 1.0f);
	std::string Res;
};

