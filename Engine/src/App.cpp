#include "pch.h"
#include "Timer/Timer.h"
#include "Engine/Engine.h"
#include "Resource/Resource.h"
#include "Events/EventSystem.h"
#include "Editor/UiLayer.h"

using namespace fr;

int main(int argc, char** argv) {
	Resource.Initialize();
	Core.Initialize("Resource/Scene/scene.fr");
	Timer.Initialize();

	while (Core.Run()) {
		Timer.Tick();
		Events.Poll();
		Core.Update();
		Core.Render();
	}

	return EXIT_SUCCESS;
}