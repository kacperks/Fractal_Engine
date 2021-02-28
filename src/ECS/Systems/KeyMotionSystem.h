#pragma once

#include <GLFW/glfw3.h>
#include "Engine/Engine.h"
#include "Inputs/Inputs.h"

#include "ECS/Core/BaseSystem.h"
#include "ECS/Components/KeyMotion.h"
#include "ECS/Components/Transform3D.h"

class KeyMotionSystem : public ECS::BaseSystem {
public:
	void OnStart() {
		AddComponentSignature<Transform3D>();
		AddComponentSignature<KeyMotion>();
	}

	void OnUpdate() {	
		float deltatime = FuseOrbit3D::Core.DeltaTime();

		for (auto entity : entities) {
			auto& transform = FuseOrbit3D::Manager.GetComponent<Transform3D>(entity);
			auto& keyMotion = FuseOrbit3D::Manager.GetComponent<KeyMotion>(entity);

			if (keyMotion.Axis == AxisType::ADSW) {
				ASDWControl(transform, keyMotion.Speed, deltatime);
				continue;
			}
			if (keyMotion.Axis == AxisType::ADSWQE) {
				ASDWQEControl(transform, keyMotion.Speed, deltatime);
				continue;
			}
			if (keyMotion.Axis == AxisType::ARROWS) {
				ARROWSControl(transform, keyMotion.Speed, deltatime);
				continue;
			}
			if (keyMotion.Axis == AxisType::NUMERIC_ARROWS) {
				NUMControl(transform, keyMotion.Speed, deltatime);
				continue;
			}
		}
	}

	void ARROWSControl(Transform3D& transform, float speed, float deltatime) {
		auto& event = Inputs::Event();

		// X-AXIS
		if (event.IsKeyPressed(GLFW_KEY_RIGHT)) {
			transform.Position.x += speed * deltatime;
		}
		if (event.IsKeyPressed(GLFW_KEY_LEFT)) {
			transform.Position.x -= speed * deltatime;
		}

		// Y-AXIS
		if (event.IsKeyPressed(GLFW_KEY_UP)) {
			transform.Position.y += speed * deltatime;
		}
		if (event.IsKeyPressed(GLFW_KEY_DOWN)) {
			transform.Position.y -= speed * deltatime;
		}
	}

	void ASDWControl(Transform3D& transform, float speed, float deltatime) {
		auto& event = Inputs::Event();
		// X-AXIS
		if (event.IsKeyPressed(GLFW_KEY_D)) {
			transform.Position.x += speed * deltatime;
		}
		if (event.IsKeyPressed(GLFW_KEY_A)) {
			transform.Position.x -= speed * deltatime;
		}

		// Y-AXIS
		if (event.IsKeyPressed(GLFW_KEY_W)) {
			transform.Position.y += speed * deltatime;
		}
		if (event.IsKeyPressed(GLFW_KEY_S)) {
			transform.Position.y -= speed * deltatime;
		}
	}

	void ASDWQEControl(Transform3D& transform, float speed, float deltatime) {
		auto& event = Inputs::Event();
		// X-AXIS
		if (event.IsKeyPressed(GLFW_KEY_D)) {
			transform.Position.x += speed * deltatime;
		}
		if (event.IsKeyPressed(GLFW_KEY_A)) {
			transform.Position.x -= speed * deltatime;
		}

		// Y-AXIS
		if (event.IsKeyPressed(GLFW_KEY_W)) {
			transform.Position.y += speed * deltatime;
		}
		if (event.IsKeyPressed(GLFW_KEY_S)) {
			transform.Position.y -= speed * deltatime;
		}

		// Z-AXIS
		if (event.IsKeyPressed(GLFW_KEY_Q)) {
			transform.Position.z += speed * deltatime;
		}
		if (event.IsKeyPressed(GLFW_KEY_E)) {
			transform.Position.z -= speed * deltatime;
		}
	}

	void NUMControl(Transform3D& transform, float speed, float deltatime) {
		auto& event = Inputs::Event();

		// X-AXIS
		if (event.IsKeyPressed(GLFW_KEY_KP_6)) {
			transform.Position.x += speed * deltatime;
		}
		if (event.IsKeyPressed(GLFW_KEY_KP_4)) {
			transform.Position.x -= speed * deltatime;
		}

		// Y-AXIS
		if (event.IsKeyPressed(GLFW_KEY_KP_8)) {
			transform.Position.y += speed * deltatime;
		}
		if (event.IsKeyPressed(GLFW_KEY_KP_2)) {
			transform.Position.y -= speed * deltatime;
		}
	}
};
