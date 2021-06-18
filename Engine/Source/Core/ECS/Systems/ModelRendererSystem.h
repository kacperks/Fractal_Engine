#pragma once
#include "Core/ECS/Base/BaseSystem.h"
#include "Core/ECS/Base/EntityManager.h"

#include "Core/Resource/Resource.h"
#include "Core/ECS/Components/Transform.h"
#include "Core/ECS/Components/ModelRenderer.h"

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