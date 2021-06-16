#pragma once

#include "pch.h"

namespace fr {
	struct FRWindow {
		GLFWwindow* window;
		Vector2i* Size = new Vector2i(1280, 720);

		DepthBuffer* shadowBuffer;
		SamplerBuffer* outputBuffer;

		FRWindow(const FRchar* title);
	};
}