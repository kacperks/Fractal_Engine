#pragma once

#include <bitset>
#include <glm/glm.hpp>

enum class MouseButton { LEFT = 0, MIDDLE = 1, RIGHT = 2 };

class Inputs {
public:
	~Inputs() = default;
	static Inputs& Event() {
		static Inputs singleton;
		return singleton;
	}

	// keyboard events
	void SetKey(int key, bool value) { keyboard[key] = value; }
	const bool IsKeyPressed(int key) { return keyboard[key]; }

	// mouse events
	void SetMouseButton(int button, bool value) { mouse[button] = value; }
	inline const glm::vec2 MouseMotionOffset() { return mouseMotionOffset; }
	inline const glm::vec2 MouseScrollOffset() { return mouseScrollOffset; }
	inline const bool IsMouseDown(MouseButton button) { return mouse[(int)button]; }
	
	inline void ResetScrollState() { onMouseScroll = false; }
	inline const bool IsMouseMoving() { return onMouseMotion; }
	inline const bool IsMouseScrolling() { return onMouseScroll; }

	void MouseSroll(double sx, double sy);
	void MouseMotion(double mx, double my);

private:
	Inputs();

private:
	bool onMouseScroll;
	bool onMouseMotion;

	std::bitset<3> mouse;
	std::bitset<1024> keyboard;

	glm::vec2 mousePrevScroll;
	glm::vec2 mousePrevPosition;
	glm::vec2 mouseMotionOffset;
	glm::vec2 mouseScrollOffset;
};


