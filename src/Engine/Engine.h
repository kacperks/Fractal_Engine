#pragma once

namespace fr {

	const int SCREEN_WIDTH(1280);
	const int SCREEN_HEIGHT(720);

	class Engine {

	public:
		~Engine();
		Engine(const Engine&) = delete;
		Engine& operator=(const Engine&) = delete;

		static Engine& Ref() {
			static Engine reference;
			return reference;
		}

		void Quit();
		void Update();
		void Initialize();

		inline const bool Run() const { return run; }
		inline GLFWwindow& Window() { return *window; }
		inline const float DispWidth() const { return dispWidth; }
		inline const float DispHeight() const { return dispHeight; }
		
	private:
		Engine();

	private:
		bool run;
		GLFWwindow* window;
		float dispWidth, dispHeight;
	};

	static Engine& Core = Engine::Ref();
}
