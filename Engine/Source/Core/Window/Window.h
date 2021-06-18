#pragma once

#include "pch.h"

namespace fr {
	struct FRWindow {
		GLFWwindow* window;

		int Width = WINDOW_WIDTH;
		int Height = WINDOW_HEIGH;

		DepthBuffer* shadowBuffer;
		SamplerBuffer* outputBuffer;

		FRWindow(const FRchar* title);
	};
}