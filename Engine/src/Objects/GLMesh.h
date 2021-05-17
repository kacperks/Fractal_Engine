#pragma once

#ifndef FR_MESH
#define FR_MESH

#include "VertexArray.h"
#include "Material.h"

class GLMesh {

public:
	GLMesh() = default;
	~GLMesh() = default;

	GLMesh(Vertex* vertices, GLsizei vSize) {
		vao = VertexArray(vertices, vSize);
	}

	GLMesh(Vertex* vertices, GLsizei vSize, GLuint* indices, GLsizei iSize) {
		vao = VertexArray(vertices, vSize, indices, iSize);
	}

	GLMesh(Vertex* vertices, GLsizei vSize, GLuint* indices, GLsizei iSize, const Material& matrial): 
		material(matrial) {
		vao = VertexArray(vertices, vSize, indices, iSize);
	}

	GLMesh(const VertexArray& vao): vao(vao) {}

	void SetMaterial(const Material& matrial) {
		material = matrial;
	}

	Material& GetMaterial() {
		return material;
	}

	void Render(Shader& shader, GLenum mode = GL_TRIANGLE_STRIP) {
		material.SetUniform(shader);
		shader.Bind();
		vao.DrawElements(mode);
	}

	void DrawArrays(Shader& shader, GLenum mode = GL_TRIANGLES) {
		material.SetUniform(shader);
		shader.Bind();
		vao.DrawArrays(mode);
	}

private:
	VertexArray vao;
	Material material;
};

#endif