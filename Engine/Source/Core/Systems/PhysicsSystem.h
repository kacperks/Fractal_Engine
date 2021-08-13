#pragma once

#include "Physics/PhysicsWorld.h"
#include "Core/Timer/Timer.h"
#include "Core/Engine.h"
#include "Scene/BaseSystem.h"
#include "Scene/EntityManager.h"
#include "Events/KeyCodes.h"
#include "Core/Components/Transform.h"
#include "Core/Components/RigidBody.h"
#include "Physics/PhysicsBody.h"

using namespace fr;

// not finished yet!

class PhysicsSystem : public ECS::BaseSystem {

public:
	PhysicsSystem() {
		AddComponentSignature<Transform>();
		AddComponentSignature<RigidBody>();
	}

	void Start() {

	}

	void Update() {
		for (auto entity : entities) {
			auto& transform = ECS::Manager.GetComponent<Transform>(entity);
			auto& rigidbody = ECS::Manager.GetComponent<RigidBody>(entity);
		}
	}
};