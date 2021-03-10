#include "fractal.hpp"

using namespace fr;

int main(int argc, char** argv) {
	Resource.Initialize();
	Core.Initialize();
	Timer.Initialize();

	while (Core.Run()) {
		Timer.Tick();
		Events.Poll();
		Core.Update();
		Core.Render();
	}

	return EXIT_SUCCESS;
}