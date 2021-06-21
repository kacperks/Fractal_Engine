#include "pch.h"
#include "Core/Timer/Timer.h"
#include "Core/Engine.h"
#include "Core/Resource/Resource.h"
#include "Events/EventSystem.h"
#include "Core/Scripting/LuaScripting.h"
#include "Editor/UiLayer.h"

using namespace fr;

int main(int argc, char** argv) {
	Core.SetCommandLineArgs({ argc, argv });
	Resource.Initialize();
	Core.Initialize();
	Timer.Initialize();
	Serializer.LoadScene("Resource/Scene/scene.fr");

	while (Core.Run()) {
		Timer.Tick();
		Events.Poll();
		Core.Update();
		Core.Render();

		#if defined(FR_BULID)
			Core.StartGame();
		#endif
	}

	return FR_NULL;
}