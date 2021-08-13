#pragma once

#include "pch.h"

#include "Math/Vector2.h"

namespace fr {
	class FRWindow {
		public:
			FRWindow(const FRchar* title);

			GLFWwindow* GetWindow() { return window; }
			Vec2* GetSize() { return Size; }
			DepthBuffer* GetDepthBuffer() { return shadowBuffer; }
			SamplerBuffer* outputBuffer;

			void SetVsync(int interval) { glfwSwapInterval(interval); }
		private:
			GLFWwindow* window;
			Vec2* Size = new Vec2(WINDOW_WIDTH, WINDOW_HEIGH);
			DepthBuffer* shadowBuffer;
	};
}