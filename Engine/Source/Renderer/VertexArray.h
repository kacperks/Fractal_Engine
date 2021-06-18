#pragma once

#include "Vertex.h"

using namespace fr;

class VertexArray {
public:
	~VertexArray() = default;

	VertexArray(): VAO(0), EBO(0), VBO(0), numOfIndices(0),
		numOfVertices(0) {}

	VertexArray(Vertex* vertices, GLsizei vSize, GLuint* indices=nullptr, GLsizei iSize=0): 
		numOfIndices(iSize), numOfVertices(vSize){
		glGenVertexArrays(1, &VAO);
		glGenBuffers(1, &VBO);
		glGenBuffers(1, &EBO);
		
		glBindVertexArray(VAO);
		glBindBuffer(GL_ARRAY_BUFFER, VBO);
		glBufferData(GL_ARRAY_BUFFER, numOfVertices * sizeof(Vertex), vertices, GL_STATIC_DRAW);
		
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, numOfIndices * sizeof(GLuint), indices, GL_STATIC_DRAW);
		
		// Positions
		glEnableVertexAttribArray(0);
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (GLvoid*)0);
		// Normals
		glEnableVertexAttribArray(1);
		glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (GLvoid*)offsetof(Vertex, Normal));
		// Texcoords
		glEnableVertexAttribArray(2);
		glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (GLvoid*)offsetof(Vertex, TexCoords));

		glBindVertexArray(0);
		numOfVertices /= sizeof(Vertex);
	}

	void PushAttrib(GLuint index, GLint size, GLsizei stride, GLvoid* ptr) {
		glEnableVertexAttribArray(index);
		glVertexAttribPointer(index, size, GL_FLOAT, GL_FALSE, size, ptr);
	}

	void Bind() {
		GLCALL(glBindVertexArray(VAO));
	}

	void UnBind() {
		GLCALL(glBindVertexArray(0));
	}

	void DrawElements(GLenum mode = GL_TRIANGLE_STRIP) {
		GLCALL(glBindVertexArray(VAO));
		GLCALL(glDrawElements(mode, numOfIndices, GL_UNSIGNED_INT, 0));
		GLCALL(glBindVertexArray(0));
	}

	void DrawArrays(GLenum mode = GL_TRIANGLES) {
		GLCALL(glBindVertexArray(VAO));
		GLCALL(glDrawArrays(mode, 0, numOfVertices));
		GLCALL(glBindVertexArray(0));
	}

private:
	GLuint VAO, VBO, EBO;
	GLsizei numOfIndices, numOfVertices;
};