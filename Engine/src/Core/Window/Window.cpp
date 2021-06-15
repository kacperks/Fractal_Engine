#include "pch.h"

#include "Window.h"

namespace fr {
	FRWindow::FRWindow(FRchar* title) {
		glfwInit();
		glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
		glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 1);
		glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);

		auto vMode = glfwGetVideoMode(glfwGetPrimaryMonitor());

		glfwWindowHint(GLFW_SAMPLES, 4);
		glfwWindowHint(GLFW_MAXIMIZED, GL_TRUE);
		glfwWindowHint(GLFW_RED_BITS, vMode->redBits);
		glfwWindowHint(GLFW_BLUE_BITS, vMode->blueBits);
		glfwWindowHint(GLFW_GREEN_BITS, vMode->greenBits);
		glfwWindowHint(GLFW_REFRESH_RATE, vMode->refreshRate);

		window = glfwCreateWindow(Size->x, Size->y, title, nullptr, nullptr);
		assert(window && "Failed To Create Window!!");
		glfwMakeContextCurrent(window);

		assert(glewInit() == GLEW_OK && "Glew init Failed!!");
		glewExperimental = GL_TRUE;

		GLCALL(glEnable(GL_STENCIL_TEST));
		GLCALL(glEnable(GL_DEPTH_TEST));
		GLCALL(glEnable(GL_MULTISAMPLE))

		shadowBuffer = new DepthBuffer(1024, 1024);
		outputBuffer = new SamplerBuffer(Size->x, Size->y);
		GLCALL(glViewport(0, 0, Size->x, Size->y));
	}
}