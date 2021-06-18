#pragma once

#include "Renderer/Shader.h"
#include "Core/ECS/Base/BaseComponent.h"

constexpr glm::vec3 RIGHT = glm::vec3(1, 0, 0);
constexpr glm::vec3 FRONT = glm::vec3(0, 0, -1);
constexpr glm::vec3 WORLD_UP = glm::vec3(0, 1, 0);

struct Camera : public ECS::BaseComponent {
	float zNear = 0.1f;
	float zFar = 1000.0f;
	float FieldOfView = 45.0f;
	glm::vec3 Rotation = glm::vec3(0);
	glm::vec3 Position = glm::vec3(0, 0, 3);

	void SetUniformVP(Shader& shader, glm::vec2 dispsize, float tFactor = 1.0f) {
		shader.Bind();
		shader.SetMatrix4f("View", glm::value_ptr(GetView(tFactor)));
		shader.SetMatrix4f("Projection", glm::value_ptr(GetProj(dispsize)));
	}

	const glm::vec3 CastRay(glm::vec2 dispsize, glm::vec2 pos) {

		glm::vec2 mouseNdc = (2.0f * pos) / dispsize - glm::vec2(1.0f);
		mouseNdc.y = -mouseNdc.y; //origin is top-left and +y mouse is down

		// from ndc to clip
		glm::vec4 clipCoords(mouseNdc.x, mouseNdc.y, -1.0f, 1.0f);

		// from clip to view
		glm::vec4 viewCoord = glm::inverse(GetProj(dispsize)) * clipCoords;
		viewCoord.z = -1.0f;
		viewCoord.w = 0.0f;

		// from view to wolrd
		glm::vec4 wolrdCoord = glm::inverse(GetView()) * viewCoord;

		// normalize ray vector
		glm::vec3 ray = glm::normalize(glm::vec3(wolrdCoord.x, wolrdCoord.y, wolrdCoord.z));

		std::cout << ray.x << " " << ray.y << " " << ray.z << std::endl;
		return ray;
	}

	glm::mat4 GetView(float tFactor = 1.0f) {
		glm::vec3 position = Position * tFactor;
		glm::mat4 view = glm::lookAt(position, (position + FRONT), WORLD_UP);
		view = glm::rotate(view, glm::radians(Rotation.x), glm::vec3(1, 0, 0));
		view = glm::rotate(view, glm::radians(Rotation.y), glm::vec3(0, 1, 0));
		view = glm::rotate(view, glm::radians(Rotation.z), glm::vec3(0, 0, 1));
		return view;
	}

	glm::mat4 GetProj(glm::vec2 size) {
		return glm::perspective(FieldOfView, size.x / size.y, zNear, zFar);
	}
};
