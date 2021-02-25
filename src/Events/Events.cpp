#include "../fractal.hpp"
#include "Events.h"

namespace fr {

	// callback function definition
	void WindowCloseCallback(GLFWwindow* window);

	Events::Events() { }

	Events::~Events() { }

	void Events::Poll() {
		glfwPollEvents();
	}

	void Events::Initialiaze() {
		GLFWwindow& window = Core.Window();
		glfwSetWindowCloseCallback(&window, WindowCloseCallback);
	}

	// callback function implementation

	void WindowCloseCallback(GLFWwindow* window) {		
		FO3D::Core.Quit();
	}
}
