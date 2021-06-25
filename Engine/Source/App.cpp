#include "pch.h"
#include "Core/Timer/Timer.h"
#include "Core/Engine.h"
#include "Core/Resource/Resource.h"
#include "Events/EventSystem.h"
#include "Core/Scripting/LuaScripting.h"
#include "Editor/UiLayer.h"

using namespace fr;

LuaScripting Lua;

int main(int argc, char** argv) {
	Core.SetCommandLineArgs({ argc, argv });
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