#pragma once
#include "pch.h"
#include "Engine/Engine.h"
#include "Events/EventSystem.h"

#include "ECS/Components.h"
#include "ECS/Components/GravitySimulation.h"

#include "ECS/Base/Entity.h"
#include "Serializer/XMLSerializer.h"

using namespace fr;

// not finished yet

class GravitySystem : public ECS::BaseSystem {

public:
	GravitySystem() {
		AddComponentSignature<Transform>();
		AddComponentSignature<RigidBody>();
		AddComponentSignature<Gravity>();
	}

	void Start() {
		for (auto entity : entities) {
			auto& transform = ECS::Manager.GetComponent<Transform>(entity);
			auto& rigidbody = ECS::Manager.GetComponent<RigidBody>(entity);
			auto& gravity = ECS::Manager.GetComponent<Gravity>(entity);

			gravity.CurrentVelocity = gravity.InitialVelocity;
		}
	}

	void Update() {
		for (auto entity : entities) {
			auto& transform = ECS::Manager.GetComponent<Transform>(entity);
			auto& rigidbody = ECS::Manager.GetComponent<RigidBody>(entity);
			auto& gravity = ECS::Manager.GetComponent<Gravity>(entity);

			UpdateVelocity(1, transform.Position, gravity);
		}
	}

	void UpdateVelocity(float timestep, glm::vec3 BodyPos1, Gravity gc) {
		glm::vec3 force = force * gc.GravitionalConstant * gc.Mass;
		glm::vec3 accleration = force / gc.Mass;

		gc.CurrentVelocity += accleration * timestep;
	}

	void UpdatePosition(float timestep, Transform transform, Gravity gravity) {
		transform.Position += gravity.CurrentVelocity * timestep;
	}
private:

};
