#pragma once

#include "pch.h"
#include "GLFWImp.h"
#include "EventSystem.h"

namespace GlfwImpl {

	static MouseData& mouse = Events.MouseRef();
	static KeyBoard& keys = Events.KeyboardRef();

	void WindowCloseCallback(GLFWwindow* window) {
		Dispatcher.Post(WindowEvent());
		Dispatcher.Post(WindowCloseEvent());
	}

	void WindowResizedCallback(GLFWwindow* window, int width, int height) {
		Dispatcher.Post(WindowEvent());
		Dispatcher.Post(WindowResizedEvent(width, height));
	}

	void KeyboardCallback(GLFWwindow* window, int key, int scancode, int action, int mode) {
		switch (action) {
			case GLFW_PRESS: 
				keys.set(key);
				Dispatcher.Post(KeyPressedEvent()); 
				break;

			case GLFW_RELEASE:
				keys.reset(key);
				Dispatcher.Post(KeyReleasedEvent());  
				break;
		}

		Dispatcher.Post(KeyEvent());
	}

	void MouseButtonCallback(GLFWwindow* window, int button, int action, int mod) {
		switch (action) {
			case GLFW_PRESS: 				
				Dispatcher.Post(MousePressEvent(mouse));				
				mouse.buttons.set(button);
				break;

			case GLFW_RELEASE: 
				Dispatcher.Post(MouseReleaseEvent(mouse));
				mouse.buttons.reset(button);
				break;
		}	

		Dispatcher.Post(MouseEvent(mouse));
	}

	void MouseMotionCallback(GLFWwindow* window, double x, double y) {
		mouse.lastX = mouse.posX;
		mouse.lastY = mouse.posY;
		mouse.posX = x;
		mouse.posY = y;
		Dispatcher.Post(MouseMotionEvent(mouse));
		Dispatcher.Post(MouseEvent(mouse));
	}

	void MouseScrollCallback(GLFWwindow* window, double x, double y) {
		mouse.scrollX = x;
		mouse.scrollY = y;
		Dispatcher.Post(MouseScrollEvent(mouse));
		Dispatcher.Post(MouseEvent(mouse));
	}
}