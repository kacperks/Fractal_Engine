#pragma once

#include "Engine/Engine.h"
#include "Resource/Resource.h"

#include "ECS/Base/BaseSystem.h"
#include "ECS/Base/EntityManager.h"

#include "ECS/Components/Camera.h"
#include "ECS/Components/Transform.h"

using namespace fr;

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