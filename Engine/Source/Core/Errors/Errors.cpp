#include "pch.h"
#include "Errors.h"

#include <termcolor/termcolor.hpp>
namespace fr {
	bool GLLogCall(const char* function, const char* file, int line) {
		while (GLenum error = glGetError()) {
			std::cout << termcolor::red << "GL Error! :"<< termcolor::bright_blue << file << " Line: "<< line << termcolor::white <<std::endl;
			return false;
		}
		return true;
	}

	void GLClearError() {
		while (glGetError() != GL_NO_ERROR);
	}

}