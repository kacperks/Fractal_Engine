#pragma once

#include "pch.h"

#define ASSERT(boolean) if (!(boolean)) __debugbreak();
#define GLCALL(func) GLClearError(); func; ASSERT(GLLogCall(#func, __FILE__, __LINE__))

static void GLClearError() {
	while (glGetError() != GL_NO_ERROR);
}

static bool GLLogCall(const char* function, const char* file, int line) {
	while (GLenum error = glGetError()) {
		std::cout <<
			"\nOPENGL::RUNTIME::ERROR::[ " << error << " ]\n"
			"FUNCTION::[ " << function << " ]\n"
			"FILE::[ " << file << " ]\n"
			"LINE::[ " << line << " ]"
			<< std::endl;
		return false;
	}
	return true;
}
