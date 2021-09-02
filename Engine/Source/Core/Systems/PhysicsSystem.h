#pragma once

#include "Physics/PhysicsWorld.h"
#include "Core/Timer/Timer.h"
#include "Core/Engine.h"
#include "Scene/BaseSystem.h"
#include "Scene/EntityManager.h"
#include "Events/KeyCodes.h"
#include "Core/Components/Transform.h"
#include "Core/Components/RigidBody.h"
#include "Physics/PhysicsWorld.h"
#include "Physics/PhysicsBody.h"

using namespace fr;

class PhysicsSystem : public ECS::BaseSystem {

public:
	PhysicsSystem() {
		AddComponentSignature<Transform>();
		AddComponentSignature<RigidBody>();
	}

	void Update() {
		m_PhysicsEngine.Step();
		m_PhysicsEngine.ResolveCollisions();
	}
private:
	Physics::PhysicsWorld m_PhysicsEngine;
};