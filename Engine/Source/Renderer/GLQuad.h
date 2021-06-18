#pragma once

#include "VertexArray.h"

using namespace fr;

class GLQuad {
public:
	~GLQuad() = default;

	GLQuad() {
		Vertex vertices[] = {
			Vertex(glm::vec3(-0.5f,  -0.5f, 0.0f), glm::vec3(0), glm::vec2(0.0f, 0.0f)),
			Vertex(glm::vec3( 0.5f,  -0.5f, 0.0f), glm::vec3(0), glm::vec2(1.0f, 0.0f)),
			Vertex(glm::vec3( 0.5f,   0.5f, 0.0f), glm::vec3(0), glm::vec2(1.0f, 1.0f)),
			Vertex(glm::vec3(-0.5f,   0.5f, 0.0f), glm::vec3(0), glm::vec2(0.0f, 1.0f))
		};

		GLuint indices[] = {
			0, 1, 2,
			2, 3, 0
		};

		VAO = VertexArray(vertices, 4, indices, 6);
	}

	VertexArray VAO;
};