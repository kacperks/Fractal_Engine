#include "pch.h"
#include "Timer.h"
#include "Core/Log.h"

namespace fr {

	T_Timer::T_Timer() : deltaTime(0.0f), lastFrame(0.0f) {

	}

	void T_Timer::Initialize() {
		INFO("Timer Initialized!");
	}

	void T_Timer::Tick() {
		deltaTime = glfwGetTime() - lastFrame;
		lastFrame = glfwGetTime();
	}
}