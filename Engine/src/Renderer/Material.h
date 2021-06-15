#pragma once

#include "Renderer/Shader.h"

using namespace fr;

struct Material {
	Material() = default;
	~Material() = default;
	Material(glm::vec3 albedo, GLfloat metallic, GLfloat roughness, GLfloat ao):
		Albedo(albedo), Metallic(metallic), Roughness(roughness), Ao(ao) { }

	GLfloat Ao = 1.0f;
	GLfloat Metallic = 0.1f;
	GLfloat Roughness = 0.9f;
	glm::vec3 Albedo = glm::vec3(0.6f);

	GLuint AoMap = 0;
	GLuint NormalMap = 0;
	GLuint AlbedoMap = 0;
	GLuint MetallicMap = 0;
	GLuint RoughnessMap = 0;

	void SetUniform(Shader& shader) {
		shader.Bind();
		shader.Set1f("material.Ao", Ao);
		shader.SetV3f("material.Albedo", Albedo);
		shader.Set1f("material.Metallic", Metallic);
		shader.Set1f("material.Roughness", Roughness);

		shader.SetSample2D("AoMap", AoMap, 0);
		shader.SetSample2D("AlbedoMap", AlbedoMap, 1);
		shader.SetSample2D("NormalMap", NormalMap, 2);
		shader.SetSample2D("MetallicMap", MetallicMap, 3);
		shader.SetSample2D("RoughnessMap", RoughnessMap, 4);
	}
};