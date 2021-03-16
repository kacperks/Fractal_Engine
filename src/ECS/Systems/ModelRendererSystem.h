#pragma once
#include "../Base/BaseSystem.h"
#include "../Base/EntityManager.h"

#include "../../Resource/Resource.h"
#include "../Components/Transform.h"
#include "../Components/ModelRenderer.h"

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