#pragma once

#include "Timer/Timer.h"
#include "Engine/Engine.h"
#include "ECS/Base/BaseSystem.h"
#include "ECS/Base/EntityManager.h"

#include "ECS/Components/Transform.h"
#include "ECS/Components/RigidBody.h"
#include "ECS/Components/GravitySimulation.h"
#include "ECS/ECS.h"

#include "pch.h"
#include "Editor/UiLayer.h"
#include "Engine/Engine.h"
#include "Events/EventSystem.h"

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
			ECS::EntityID* AllBodies[1];

			auto& transform = ECS::Manager.GetComponent<Transform>(entity);
			auto& rigidbody = ECS::Manager.GetComponent<RigidBody>(entity);
			auto& gravity = ECS::Manager.GetComponent<Gravity>(entity);

			UpdateVelocity(1, transform  , rigidbody , gravity , entity , 4);
		}
	}

	void UpdateVelocity(float timestep, Transform t , RigidBody rb , Gravity g , ECS::EntityID id, int otherbody) {
			glm::vec3 forceDir = (ECS::Manager.GetComponent<Transform>(otherbody).Position - ECS::Manager.GetComponent<Transform>(id).Position);
			glm::vec3 force;
			glm::vec3 accleration = force / g.Mass;

			g.CurrentVelocity += accleration * timestep;
	}

	void UpdatePosition(float timestep) {
		for (auto entity : entities) {
			auto& transform = ECS::Manager.GetComponent<Transform>(entity);
			auto& gravity = ECS::Manager.GetComponent<Gravity>(entity);
			
			transform.Position += gravity.CurrentVelocity * timestep;
		}
	}
private:

};
