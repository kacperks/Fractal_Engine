#pragma once

namespace fr {

	class T_Timer {

	public:
		T_Timer();

		void Tick();
		void Initialize();
		inline float DeltaTime() { return deltaTime; }
	private:
		float lastFrame, deltaTime;
	};

	static T_Timer Timer;
}