#include "pch.h"
#include "Core/Log.h"
#include "Core/Timer/Timer.h"
#include "Core/Engine.h"
#include "Core/Resource/Resource.h"
#include "Events/EventSystem.h"
#include "Editor/UiLayer.h"

using namespace fr;

int main(int argc, char** argv) {
	INFO("Cool");
	Resource.Initialize();
	Core.Initialize();
	Timer.Initialize();
	Core.SetCurrentScene("Resource/scene/scene.fr");

	while (Core.Run()) {
		Timer.Tick();
		Events.Poll();
		Core.Update();
		Core.Render();
	}

	return FR_NULL;
}