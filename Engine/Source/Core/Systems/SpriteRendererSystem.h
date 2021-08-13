#pragma once

#include "Renderer/GLQuad.h"
#include "Core/Resource/Resource.h"
#include "Scene/BaseSystem.h"
#include "Scene/EntityManager.h"

#include "Core/Components/Transform.h"
#include "Core/Components/SpriteRenderer.h"

using namespace fr;

class SpriteRendererSystem : public ECS::BaseSystem {

public:
	SpriteRendererSystem() {
		AddComponentSignature<Transform>();
		AddComponentSignature<SpriteRenderer>();
		shader = Shader(Resource.Program("SPRITE"));
	}

	void Render() override {
		for (auto& entity : entities) {
			ECS::Manager.GetComponent<Transform>(entity).SetModelUniform(shader);
			ECS::Manager.GetComponent<SpriteRenderer>(entity).SetUniform(shader);
			shader.Bind();
			glEnable(GL_BLEND);
			glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
			quad.VAO.DrawElements(GL_TRIANGLES);
			glDisable(GL_BLEND);
		}
	}

private:
	GLQuad quad;
	Shader shader;
};