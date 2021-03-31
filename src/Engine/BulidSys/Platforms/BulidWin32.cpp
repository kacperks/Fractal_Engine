#include "BulidWin32.hpp"

namespace bulid {
	void Win32::BulidAll() {
		
		// C++

		BulidCpp("Resource/Scripts");
		BulidCpp("Resource/Components");

		// C#

		BulidCSM("Resource/Scripts/*.cs");

		// OpenGL 

		BulidGLSL("Resource/Shaders");
	}

	void Win32::BulidGLSL(const char* location) {

	}
};