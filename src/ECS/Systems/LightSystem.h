#pragma once

#include "Errors/ErrorLog.h"
#include "Resource/Resource.h"

#include "../Base/BaseSystem.h"
#include "../../GLObjects/Shader.h"
#include "../Components/Light.h"
#include "../Components/Transform3D.h"


class LightSystem : public ECS::BaseSystem {

public:
	LightSystem(){}

	void OnStart() {
		AddComponentSignature<Light>();
		AddComponentSignature<Transform3D>();

		shader = Shader(RESOURCE.GetShader("SHADER"));
		skyboxShader = Shader(RESOURCE.GetShader("SKYBOX"));
	}

	void OnUpdate() {	
		int LightIndex = 0;
		for (auto entity : entities) {
			auto& light = FuseOrbit3D::Manager.GetComponent<Light>(entity);
			auto& transform = FuseOrbit3D::Manager.GetComponent<Transform3D>(entity);

			// light[i].attribute
			std::string type = LightAttribute(LightIndex, ".type");
			std::string ambient = LightAttribute(LightIndex, ".ambient");
			std::string diffuse = LightAttribute(LightIndex, ".diffuse");
			std::string specular = LightAttribute(LightIndex, ".specular");
			std::string innerCutoff = LightAttribute(LightIndex, ".innerCutOff");
			std::string outerCutoff = LightAttribute(LightIndex, ".outerCutOff");
			std::string position = LightAttribute(LightIndex, ".position");
			std::string direction = LightAttribute(LightIndex, ".direction");
			std::string linear = LightAttribute(LightIndex, ".linear");
			std::string constant = LightAttribute(LightIndex, ".constant");
			std::string quadratic = LightAttribute(LightIndex, ".quadratic");
			LightIndex++;

			shader.Bind();
			shader.Set1i(type.c_str(), light.Type);
			shader.SetV3f(ambient.c_str(), light.Ambient);
			shader.SetV3f(diffuse.c_str(), light.Diffuse);
			shader.SetV3f(specular.c_str(), light.Specular);

			shader.Set1f(innerCutoff.c_str(), light.InnerCutOff);
			shader.Set1f(outerCutoff.c_str(), light.OuterCutOff);

			shader.SetV3f(direction.c_str(), light.Direction);
			shader.SetV3f(position.c_str(), transform.Position);

			shader.Set1f(linear.c_str(), light.Linear);
			shader.Set1f(constant.c_str(), light.Constant);
			shader.Set1f(quadratic.c_str(), light.Quadratic);
			shader.Set1i("lightSourceCount", entities.size());
			shader.UnBind();

			skyboxShader.Bind();
			skyboxShader.SetV3f("Ambient", light.Ambient);
			skyboxShader.SetV3f("Diffuse", light.Diffuse);
			skyboxShader.SetV3f("Specular", light.Specular);
			skyboxShader.UnBind();
		}
	}

private:
	std::string LightAttribute(int index, std::string name) {
		std::string attrib("lights[");
		attrib.append(std::to_string(index));
		attrib.append("]");
		attrib.append(name);
		return attrib;
	}

private:
	Shader shader, skyboxShader;
};

