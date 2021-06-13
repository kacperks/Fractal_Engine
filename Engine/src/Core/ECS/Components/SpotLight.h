#pragma once

#include "pch.h"

struct SpotLight : public ECS::BaseComponent {
	SpotLight() = default;
	~SpotLight() = default;

	GLfloat Linear = 0.04f;
	GLfloat Constant = 1.0f;
	GLfloat Quadratic = 0.006f;
	GLfloat ICutOff = glm::cos(glm::radians(5.0f));
	GLfloat OCutOff = glm::cos(glm::radians(120.0f));

	GLfloat Intensity = 1.0f;
	glm::vec3 Color = glm::vec3(1.0f);
	glm::vec3 Direction = glm::vec3(0.0f, 0.0f, 1.0f);
};
