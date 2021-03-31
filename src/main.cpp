#include "fractal.hpp"

using namespace fr;

bool start = true;
const char* SceneName;
char buf[20];

int main(int argc, char** argv) {

	SceneName = "Resource/Scene/scene.fr";
	if (start == true) {
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

}