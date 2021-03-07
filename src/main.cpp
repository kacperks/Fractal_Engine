#include "fractal.hpp"

void NCS(){
	Managers::Script script;
	script.Filename = "../res/Scripts/New.cs"
	Managers::NewScript(script);
}

int main(int argc, char** argv) {

	fr::Core.Initialize();

	while (fr::Core.OnRunApp()) {
		fr::Core.Update();
	}

	return fr::EXIT_PROG_SUCCESS;
}