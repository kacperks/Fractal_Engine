#pragma once

namespace GlfwImpl {
	void WindowCloseCallback(GLFWwindow* window);
	void WindowResizedCallback(GLFWwindow* window, int width, int height);
	void KeyboardCallback(GLFWwindow* window, int key, int scancode, int action, int mode);
	void MouseButtonCallback(GLFWwindow* window, int button, int action, int mod);
	void MouseMotionCallback(GLFWwindow* window, double x, double y);
	void MouseScrollCallback(GLFWwindow* window, double x, double y);
}