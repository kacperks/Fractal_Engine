#pragma once
#include "Scene/BaseSystem.h"
#include "Scene/EntityManager.h"

#include "Core/Resource/Resource.h"
#include "Core/Components/Transform.h"
#include "Core/Components/ModelRenderer.h"

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