#pragma once

#include "Core/Engine.h"
#include "Core/Resource/Resource.h"
#include "Scene/BaseSystem.h"
#include "Scene/EntityManager.h"
#include "Core/Components/Camera.h"
#include "Core/Components/Transform.h"

class CameraSystem : public ECS::BaseSystem {

public:
	CameraSystem() {
		AddComponentSignature<Camera>();
		AddComponentSignature<Transform>();

		skybox = Shader(Resource.Program("SKYBOX"));
		shaders[0] = Shader(Resource.Program("MESH"));
	}

	void Update() {
		for (auto entity : entities) {
			auto& camera = ECS::Manager.GetComponent<Camera>(entity);
			auto& transform = ECS::Manager.GetComponent<Transform>(entity);

			camera.Position = transform.Position;
			camera.Rotation = transform.Rotation;

			camera.SetUniformVP(skybox, Core.ViewSize(), 0);
			for (auto& shader : shaders) {
				camera.SetUniformVP(shader, Core.ViewSize());
			}	
		}
	}

private:
	Shader skybox;
	Shader shaders[1];
};