#pragma once

#include <GL/glew.h>
#include <GLM/ext/vector_float3.hpp>
#include "ECS/Core/BaseComponent.h"

struct Material : public ECS::BaseComponent {
	Material() = default;
	~Material() = default;
	Material(GLuint diffuseTexture) : DiffuseTextureID(diffuseTexture), SpecularTextureID(diffuseTexture) {}
	Material(GLuint diffuseTexture, GLuint specularTexture) : DiffuseTextureID(diffuseTexture), SpecularTextureID(specularTexture) {}

	float Shininess = 0.2f;
	int DiffuseTextureID = 0;
	int SpecularTextureID = 0;

	glm::vec3 Ambient = glm::vec3(0.24f, 0.19f, 0.07f);
	glm::vec3 Diffuse = glm::vec3(0.75f, 0.61f, 0.22f);
	glm::vec3 Specular = glm::vec3(0.62f, 0.55f, 0.36f);
};