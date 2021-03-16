#pragma once

#include "../../Timer/Timer.h"
#include "../../Engine/Engine.h"
#include "../Base/BaseSystem.h"
#include "../Base/EntityManager.h"

#include "../Components/Transform.h"
#include "../Components/RigidBody.h"

using namespace fr;

class PhysicsSystem : public ECS::BaseSystem {

public:
	PhysicsSystem() {
		AddComponentSignature<Transform>();
		AddComponentSignature<RigidBody>();
	}

	void Update() {
		for (auto entity : entities) {
			auto& transform = ECS::Manager.GetComponent<Transform>(entity);
			auto& rigidbody = ECS::Manager.GetComponent<RigidBody>(entity);

			rigidbody.Force += GRAVITY * (rigidbody.Mass * rigidbody.GravityScale);
			rigidbody.Velocity += rigidbody.Force / rigidbody.Mass * Timer.DeltaTime();
			transform.Position += rigidbody.Velocity * Timer.DeltaTime();
			rigidbody.Force = glm::vec3(0);			
		}
	}
};
