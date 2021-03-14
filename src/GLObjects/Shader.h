#pragma once

#include "../fractal.hpp"

class Shader {

public:
	Shader() : program(0) {}
	Shader(const GLuint id) : program(id) {}

	void Bind() {
		GLCALL(glUseProgram(program));
	}

	void UnBind() {
		GLCALL(glUseProgram(0));
	}

	void SetSample2D(const GLchar* uName, GLuint tex2d, GLint unit = 0) {
		GLCALL(glActiveTexture(GL_TEXTURE0 + unit));
		GLCALL(glBindTexture(GL_TEXTURE_2D, tex2d));
		GLCALL(glUniform1i(glGetUniformLocation(program, uName), unit));
	}

	void SetSampleCube(const GLchar* uName, GLuint cube, GLint unit = 0) {
		GLCALL(glActiveTexture(GL_TEXTURE0 + unit));
		GLCALL(glBindTexture(GL_TEXTURE_CUBE_MAP, cube));
		GLCALL(glUniform1i(glGetUniformLocation(program, uName), unit));
	}

	void Set1i(const GLchar* uName, GLint value) {
		GLCALL(glUniform1i(glGetUniformLocation(program, uName), value));
	}

	void Set1f(const GLchar* uName, GLfloat value) {
		GLCALL(glUniform1f(glGetUniformLocation(program, uName), value));
	}

	void Set2f(const GLchar* uName, GLfloat x, GLfloat y) {
		GLCALL(glUniform2f(glGetUniformLocation(program, uName), x, y));
	}

	void SetV2f(const GLchar* uName, glm::vec2 v) {
		Set2f(uName, v.x, v.y);
	}

	void Set3f(const GLchar* uName, GLfloat x, GLfloat y, GLfloat z) {
		GLCALL(glUniform3f(glGetUniformLocation(program, uName), x, y, z));
	}

	void SetV3f(const GLchar* uName, glm::vec3 v) {
		Set3f(uName, v.x, v.y, v.z);
	}

	void Set4f(const GLchar* uName, GLfloat x, GLfloat y, GLfloat z, GLfloat w) {
		GLCALL(glUniform4f(glGetUniformLocation(program, uName), x, y, z, w));
	}

	void SetV4f(const GLchar* uName, glm::vec4 v) {
		Set4f(uName, v.x, v.y, v.z, v.z);
	}

	void SetMatrix4f(const GLchar* uName, const GLfloat* mtx) {
		GLCALL(glUniformMatrix4fv(glGetUniformLocation(program, uName), 1, GL_FALSE, mtx));
	}

	GLuint Program() const {
		return program;
	}

private:
	GLuint program;
};

