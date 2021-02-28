#include "Inputs.h"
#include <iostream>
#include <glm/ext/matrix_clip_space.hpp>

#include "../fractal.hpp"

// callback function definition
static void window_close_callback(GLFWwindow* window);
static void MouseScrollCallback(GLFWwindow* window, double sx, double sy);
static void MouseMotionCallback(GLFWwindow* window, double mx, double my);
static void WindowResizedCallback(GLFWwindow* window, int width, int height);
static void MouseButtonCallback(GLFWwindow* window, int button, int action, int mod);
static void KeyboardCallback(GLFWwindow* window, int key, int scancode, int action, int mode);

// imp of inputs
Inputs::Inputs() : mouse({ 0 }), keyboard({ 0 }), mousePrevScroll(0.0f),
	mousePrevPosition(0.0f), mouseMotionOffset(0.0f), mouseScrollOffset(0.0f), onMouseScroll(false), onMouseMotion(false){
	GLFWwindow* window = &FuseOrbit3D::Core.Window();
	glfwSetKeyCallback(window, KeyboardCallback);
	glfwSetScrollCallback(window, MouseScrollCallback);
	glfwSetCursorPosCallback(window, MouseMotionCallback);
	glfwSetMouseButtonCallback(window, MouseButtonCallback);
	glfwSetFramebufferSizeCallback(window, WindowResizedCallback);
	glfwSetWindowCloseCallback(window, window_close_callback);
	//glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
}

void Inputs::MouseSroll(double sx, double sy) {
	mouseScrollOffset = glm::vec2(sx, sy);
	onMouseScroll = true;
}

void Inputs::MouseMotion(double mx, double my) {
	onMouseMotion = false;
	if (mousePrevPosition.x != mx || mousePrevPosition.y != my) {
		mouseMotionOffset.x = (mx - mousePrevPosition.x);
		mouseMotionOffset.y = (my - mousePrevPosition.y);
		mousePrevPosition = glm::vec2(mx, my);
		onMouseMotion = true;
	}
}

// callback function implementation
static void MouseScrollCallback(GLFWwindow* window, double sx, double sy) {
	Inputs::Event().MouseSroll(sx, sy);
}

static void MouseMotionCallback(GLFWwindow* window, double mx, double my) {
	Inputs::Event().MouseMotion(mx, my);
}

static void WindowResizedCallback(GLFWwindow* window, int width, int height) {
	glViewport(0, 0, width, height);
	FuseOrbit3D::Core.UpdateScreenSize(width, height);
}

static void MouseButtonCallback(GLFWwindow* window, int button, int action, int mod) {
	switch (action) {
		case GLFW_PRESS: Inputs::Event().SetMouseButton(button, true); break;
		case GLFW_RELEASE: Inputs::Event().SetMouseButton(button, false); break;
	}
}

static void KeyboardCallback(GLFWwindow* window, int key, int scancode, int action, int mode) {
	auto& event = Inputs::Event();

	switch (action) {
		case GLFW_PRESS: event.SetKey(key, true); break;
		case GLFW_RELEASE: event.SetKey(key, false); break;
	}

	if (event.IsKeyPressed(GLFW_KEY_ESCAPE) && FuseOrbit3D::Core.mode != OperationMode::EDIT_MODE) {
		FuseOrbit3D::Core.mode = OperationMode::EDIT_MODE;		
	}
}

static void window_close_callback(GLFWwindow* window) {
	FuseOrbit3D::Core.Quit();
	glfwSetWindowShouldClose(window, GLFW_TRUE);
}