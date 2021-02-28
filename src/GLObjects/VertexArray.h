#pragma once

#include <GL/glew.h>
#include "../Errors/ErrorLog.h"

class VertexArray {

public:
	VertexArray(): VAO(0), First(0), RenderMode(0), VertexCount(0) { }

	VertexArray(GLuint vao, GLint first, GLint count, GLenum mode): 
		VAO(vao), First(first), RenderMode(mode), VertexCount(count) {
		GLCALL(glBindVertexArray(VAO));
	}

	void Bind() {
		GLCALL(glBindVertexArray(VAO));
	}

	void UnBind() {
		GLCALL(glBindVertexArray(0));
	}

	void Draw() {
		GLCALL(glBindVertexArray(VAO));
		GLCALL(glDrawArrays(RenderMode, First, VertexCount));
		GLCALL(glBindVertexArray(0));
	}

private:
	GLuint VAO;
	GLint First;
	GLenum RenderMode;
	GLint VertexCount;
};