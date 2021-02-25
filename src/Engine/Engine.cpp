#include "../fractal.hpp"
#include "Engine.h"

namespace FO3D {

	Engine::Engine() : run(true), window(NULL), dispWidth(SCREEN_WIDTH), dispHeight(SCREEN_HEIGHT) {

		glfwInit();
		glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
		glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 1);
		glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);

		auto& monitor = *glfwGetVideoMode(glfwGetPrimaryMonitor());

		glfwWindowHint(GLFW_RED_BITS, monitor.redBits);
		glfwWindowHint(GLFW_BLUE_BITS, monitor.blueBits);
		glfwWindowHint(GLFW_GREEN_BITS, monitor.greenBits);
		glfwWindowHint(GLFW_REFRESH_RATE, monitor.refreshRate);

		window = glfwCreateWindow(dispWidth, dispHeight, "FO3D", nullptr, nullptr);
		assert(window && "ERROR::GFLW::FAILED TO CREATE WINDOW!");
		glfwMakeContextCurrent(window);

		assert(glewInit() == GLEW_OK && "ERROR::GLEW::INIT FAILED!");
		glewExperimental = GL_TRUE;
	}

	Engine::~Engine() {
		glfwTerminate();
	}

	void Engine::Initialize() {

	}

	void Engine::Update() {
		
	}

	void Engine::Quit() {
		glfwSetWindowShouldClose(window, GLFW_TRUE);
		run = false;
	}
}