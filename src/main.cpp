#include "fractal.hpp"

int main(int argc, char** argv) {

	fr::Core.Initialize();

	while (fr::Core.OnRunApp()) {
		fr::Core.Update();
	}

	return fr::EXIT_PROG_SUCCESS;
}