#pragma once

#include "../Base/BaseSystem.h"
#include "../Base/EntityManager.h"

#include "../../GLObjects/Shader.h"
#include "../../GLObjects/GLMesh.h"
#include "../Components/Transform.h"

class GridRendererSystem : public ECS::BaseSystem {

public:
    GridRendererSystem() {
        shader = Shader(Resource.Program("GRID"));
	}

	void Render() override {
        shader.Bind();
        shader.SetV4f("params", glm::vec4(10.0));
	}

	void GenerateGrid(int N) {

        float scale = 20;
        int depth = 100;
        int width = 1200;

        int cols = width/scale;
        int rows = depth/scale;

        std::vector<Vertex> vertices;

        for (int z=0; z < rows; z++) {
            for(int x=0; x < cols; x++){
                vertices.push_back(Vertex(x * scale, 0, z*scale));
                vertices.push_back(Vertex(x * scale, 0, (z+1)*scale));
            }
        }


        mesh = GLMesh(vertices.data(), vertices.size());
	}

private:
    Shader shader;
    GLMesh mesh;
};