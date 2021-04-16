#include "fractal.hpp"

using namespace fr;

const char* SceneName;

int main(int argc, char** argv) {
	SceneName = "Resource/Scene/scene.fr";
		Resource.Initialize();
		Core.Initialize(SceneName);
		Timer.Initialize();

		while (Core.Run()) {
			Timer.Tick();
			Events.Poll();
			Core.Update();
			Core.Render();
		}

		return EXIT_SUCCESS;
}