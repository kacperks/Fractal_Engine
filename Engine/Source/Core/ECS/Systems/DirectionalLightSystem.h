#pragma once

#include "Core/ECS/Base/BaseSystem.h"
#include "Core/ECS/Base/EntityManager.h"

#include "Core/Engine.h"
#include "Core/Resource/Resource.h"
#include "Core/ECS/Components/Transform.h"
#include "Core/ECS/Components/DirectionalLight.h"

using namespace fr;

class DirectionalLightSystem : public ECS::BaseSystem {

public:
	DirectionalLightSystem() {
		AddComponentSignature<Transform>();
		AddComponentSignature<DirectionalLight>();

		shadow = Shader(Resource.Program("SHADOW"));
		shaders[0] = Shader(Resource.Program("MESH"));
		shaders[1] = Shader(Resource.Program("SKYBOX"));
	}

	void Update() {

		for (auto& shader : shaders) {
			shader.Bind();
			shader.Set1i("directLightCount", entities.size());
		}

		int index = 0;

		for (auto entity : entities) {

			auto& transform = ECS::Manager.GetComponent<Transform>(entity);
			auto& light = ECS::Manager.GetComponent<DirectionalLight>(entity);

			// Shadow Mapping

			glm::mat4 view = glm::lookAt(transform.Position, glm::vec3(0), glm::vec3(1));
			glm::mat4 proj = glm::ortho(-10.0f, 10.0f, -10.0f, 10.0f, 1.0f, 7.5f);
			glm::mat4 space = proj * view;

			shadow.Bind();
			shadow.SetMatrix4f("ViewProj", glm::value_ptr(space));

			// Other Shaders

			for (GLuint i = 0; i < 2; i++) {
				shaders[i].Bind();
				shaders[i].SetV3f(GetAttr("Color", index).c_str(), light.Color);
				shaders[i].Set1f(GetAttr("Intensity", index).c_str(), light.Intensity);
				shaders[i].SetV3f(GetAttr("Direction", index).c_str(), light.Direction);
				shaders[i].SetV3f(GetAttr("Position", index).c_str(), transform.Position);
			}

			index++;
		}
	}

private:
	std::string GetAttr(std::string attr, int index) {
		std::string uName("directLights[");
		uName.append(std::to_string(index));
		uName.append("].");
		uName.append(attr);
		return uName;
	}

private:
	Shader shadow;
	Shader shaders[2];
};