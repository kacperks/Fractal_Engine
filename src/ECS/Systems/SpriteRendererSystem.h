#pragma once 

#include "../../GLObjects/GLQuad.h"
#include "../../Resource/Resource.h"
#include "../Base/BaseSystem.h"
#include "../Base/EntityManager.h"

#include "../Components/Transform.h"
#include "../Components/SpriteRenderer.h"

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