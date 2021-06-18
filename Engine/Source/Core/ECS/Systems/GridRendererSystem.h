#pragma once

#include "Core/ECS/Base/BaseSystem.h"
#include "Core/ECS/Base/EntityManager.h"

#include "Renderer/Shader.h"
#include "Renderer/GLMesh.h"
#include "Core/ECS/Components/Transform.h"

#include "Renderer/Grid.h"

class GridRendererSystem : public ECS::BaseSystem {

public:
    GridRendererSystem() {
        shader = Shader(Resource.Program("GRID"));
		auto transform = Transform(glm::vec3(-50.f, 0.0, -50.f), glm::vec3(100.0f));
		transform.SetModelUniform(shader);
		grid.Render();
	}

    void Start() {
		grid = GLGrid(10);
    }

	void Update() override {
		shader.Bind();
		grid.Render();
	}

private:
    Shader shader;
    GLGrid grid;
};