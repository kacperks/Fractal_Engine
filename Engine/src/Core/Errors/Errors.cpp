#include "pch.h"
#include "Errors.h"
namespace fr {
	bool GLLogCall(const char* function, const char* file, int line) {
		while (GLenum error = glGetError()) {
			std::cout <<
				"\nGL Error! ->  [" << error << "] \n"
				"Function ->[ " << function << " ]\n"
				"File ->[ " << file << " ]\n"
				"Line ->[ " << line << " ]"
				<< std::endl;
			return false;
		}
		return true;
	}

	void GLClearError() {
		while (glGetError() != GL_NO_ERROR);
	}
}
