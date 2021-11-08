#include <pch.h>
#include <Core/Log.h>
#include <Core/Timer/Timer.h>
#include <Core/Engine.h>
#include <Core/Resource/Resource.h>
#include <Events/EventSystem.h>

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

	return FR_NULL;
}