#include "pch.h"
#include "Timer/Timer.h"
#include "Engine/Engine.h"
#include "Resource/Resource.h"
#include "Events/EventSystem.h"
#include "Editor/UiLayer.h"

using namespace fr;

bool start;
const char* SceneName;
char buf[20];

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