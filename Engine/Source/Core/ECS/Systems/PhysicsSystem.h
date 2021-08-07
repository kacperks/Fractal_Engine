#pragma once

#include "Physics/PhysicsWorld.h"
#include "Core/Timer/Timer.h"
#include "Core/Engine.h"
#include "Core/ECS/Base/BaseSystem.h"
#include "Core/ECS/Base/EntityManager.h"
#include "Events/KeyCodes.h"
#include "Core/ECS/Components/Transform.h"
#include "Core/ECS/Components/RigidBody.h"
#include "Physics/PhysicsBody.h"

using namespace fr;

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