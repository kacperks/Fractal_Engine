#pragma once
#include "ECS/Base/BaseSystem.h"
#include "ECS/Base/EntityManager.h"

#include "Resource/Resource.h"
#include "ECS/Components/Transform.h"
#include "ECS/Components/ModelRenderer.h"

using namespace fr;

class ModelRendererSystem : public ECS::BaseSystem {

public:

	ModelRendererSystem(){
		AddComponentSignature<Transform>();
		AddComponentSignature<ModelRenderer>();

		shader = Shader(Resource.Program("MESH"));
	}

	void Render() override {
		shader.Bind();
		for (auto entity : entities) {
			ECS::Manager.GetComponent<Transform>(entity).SetModelUniform(shader);
			ECS::Manager.GetComponent<ModelRenderer>(entity).Renderer->Render(shader);
		}
	}

private:
	Shader shader;
};