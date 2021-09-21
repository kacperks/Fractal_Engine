#include "pch.h"
#include "Core/Log.h"
#include "Core/Timer/Timer.h"
#include "Core/Engine.h"
#include "Core/Resource/Resource.h"
#include "Events/EventSystem.h"
#include "Editor/UiLayer.h"
#include "Systems/EditorCameraSystem.h"

using namespace fr;

int main(int argc, char** argv) {
	Resource.LoadModel("WTF", "Resource/Models/Nature/NatureFreePack1.obj");
	Resource.LoadModel("Car", "Resource/Models/car.obj");
	Resource.Initialize();
	Core.Initialize();
	ECS::Manager.AddEditorSystem<EditorCameraSystem>();
	UI.Initialiaze();
	Timer.Initialize();
	Serializer.LoadScene("Resource/scene/scene.fr");

	while (Core.Run()) {
		Timer.Tick();
		Events.Poll();
		Core.Update();

		if (!Core.GameRun()) {
			Core.SetViewport(UI.ViewSize());
			UI.Display();
		}
		Core.Render();
	}

	return FR_NULL;
}