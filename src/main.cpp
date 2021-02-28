#include "fractal.hpp"

int main(int argc, char** argv) {

	FuseOrbit3D::Core.Initialize();

	while (FuseOrbit3D::Core.OnRunApp()) {
		FuseOrbit3D::Core.Update();
	}

	return FuseOrbit3D::EXIT_PROG_SUCCESS;
}