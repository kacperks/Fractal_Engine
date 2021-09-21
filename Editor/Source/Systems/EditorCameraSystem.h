#pragma once

#include "Core/Engine.h"
#include "Editor/UiLayer.h"
#include "Core/Resource/Resource.h"

#include "Scene/BaseSystem.h"
#include "Scene/EntityManager.h"

#include "Core/Components/Camera.h"
#include "Core/Components/Transform.h"

using namespace fr;

constexpr auto SCROLL_SPEED = 60.0f;;

class EditorCameraSystem : public ECS::BaseSystem {

public:
	EditorCameraSystem() {
		camera.Position.z = 50.0f;
		skybox = Shader(Resource.Program("SKYBOX"));

		shaders[0] = Shader(Resource.Program("MESH"));
		shaders[1] = Shader(Resource.Program("GRID"));
		shaders[2] = Shader(Resource.Program("SPRITE"));
	}

	void Start() {		
		SetShadersUniforms();
		Dispatcher.AddListener<MouseMotionEvent>(std::bind(&EditorCameraSystem::OnDragCallback, this, _1));
		Dispatcher.AddListener<MouseScrollEvent>(std::bind(&EditorCameraSystem::OnZoomCallback, this, _1));
	}

	void Update() { }

	void SetShadersUniforms() {
		camera.SetUniformVP(skybox, UI.ViewSize(), 0);
		for (auto& shader : shaders) {
			camera.SetUniformVP(shader, UI.ViewSize());
		}
		UI.SetGizmoViewProjection(camera.GetView(), camera.GetProj(UI.ViewSize()));
	}

	void OnDragCallback(const Event& event) {
		auto e = Dispatcher.Cast<MouseEvent>(event);
		if (IsMouseOverViewport(e) && !ImGuizmo::IsUsing()) {
			if (!Events.IsKeyPressed(GLFW_KEY_LEFT_CONTROL) && Events.IsMouseDown(MOUSE_RIGHT)) {
				camera.Rotation.x -= e.DeltaY() * 2 * Timer.DeltaTime();
				camera.Rotation.y -= e.DeltaX() * 2 * Timer.DeltaTime();
				SetShadersUniforms();
			}

			if (Events.IsKeyPressed(GLFW_KEY_LEFT_CONTROL) && Events.IsMouseDown(MOUSE_RIGHT)) {
				camera.Position.x += e.DeltaX() * Timer.DeltaTime();
				camera.Position.y -= e.DeltaY() * Timer.DeltaTime();
				SetShadersUniforms();
			}
		}
	}

	void OnZoomCallback(const Event& event) {
		auto e = Dispatcher.Cast<MouseEvent>(event);
		if (IsMouseOverViewport(e)) {
			float speed = SCROLL_SPEED;
			if (Events.IsKeyPressed(GLFW_KEY_LEFT_CONTROL)) { speed *= 5; }
			camera.Position.z -= (e.SrollY() * speed * Timer.DeltaTime());
			SetShadersUniforms();
		}
	}

	bool IsMouseOverViewport(const MouseEvent& e) {
		const auto& mouse = glm::vec2(e.PosX(), e.PosY());
		const auto& view = UI.ViewportRect();
		return (mouse.x >= view.X && mouse.x <= (view.X + view.W))
			&& (mouse.y >= view.Y && mouse.y <= (view.Y + view.H));
	}

private:
	Camera camera;
	Shader skybox;
	Shader shaders[3];
};