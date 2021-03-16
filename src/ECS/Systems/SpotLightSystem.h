#pragma once

#include "../Base/BaseSystem.h"
#include "../Base/EntityManager.h"

#include "../../Resource/Resource.h"
#include "../Components/Transform.h"
#include "../Components/SpotLight.h"

using namespace fr;

class SpotLightSystem : public ECS::BaseSystem {

public:
	SpotLightSystem() {
		AddComponentSignature<SpotLight>();
		AddComponentSignature<Transform>();
		shader = Shader(Resource.Program("MESH"));
	}

	void Update() {

		shader.Bind();
		shader.Set1i("spotLightCount", entities.size());

		int index = 0;

		for (auto entity : entities) {
			auto& light = ECS::Manager.GetComponent<SpotLight>(entity);
			auto& transform = ECS::Manager.GetComponent<Transform>(entity);

			shader.Bind();
			shader.SetV3f(GetAttr("Position", index).c_str(), transform.Position);
			shader.Set1f(GetAttr("Intensity", index).c_str(), light.Intensity);
			shader.Set1f(GetAttr("ICutOff", index).c_str(), light.ICutOff);
			shader.Set1f(GetAttr("OCutOff", index).c_str(), light.OCutOff);
			shader.SetV3f(GetAttr("Color", index).c_str(), light.Color);

			index++;
		}
	}

private:
	std::string GetAttr(std::string attr, int index) {
		std::string uName("spotLights[");
		uName.append(std::to_string(index));
		uName.append("].");
		uName.append(attr);
		return uName;
	}

private:
	Shader shader;
};

