#pragma once

#include "pch.h"

#define ASSERT(boolean) if (!(boolean)) __debugbreak();
#define GLCALL(func) GLClearError(); func; ASSERT(fr::GLLogCall(#func, __FILE__, __LINE__))

namespace fr {
	extern void GLClearError();
	extern bool GLLogCall(const char* function, const char* file, int line);
}

