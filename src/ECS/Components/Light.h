#pragma once

#include <glm/trigonometric.hpp>
#include <glm/ext/vector_float3.hpp>
#include "../Base/BaseComponent.h"

struct Light : public ECS::BaseComponent {
	Light() = default;
	Light(int type) :Type(type) { }

	int Type = 0;
	glm::vec3 Ambient = glm::vec3(0.2f);
	glm::vec3 Diffuse = glm::vec3(0.5f);
	glm::vec3 Specular = glm::vec3(1.0f);

	float Linear = 0.04;
	float Constant = 1.0f; 
	float Quadratic = 0.006;

	// cutOff angle for spot light
	float InnerCutOff = glm::cos(glm::radians(5.0f));
	float OuterCutOff = glm::cos(glm::radians(120.0f));

	// direction for directional light
	glm::vec3 Direction = glm::vec3(0.0f, 100.0f, -100.0f);
};

