#pragma once

#include "../../Engine/Engine.h"
#include "../Base/BaseSystem.h"
#include "../Components/Transform3D.h"
#include "../Components/RigidBody3D.h"


class PhysicsSystem : public ECS::BaseSystem {

public:
	PhysicsSystem() = default;
	~PhysicsSystem() = default;

	void OnStart() {
		AddComponentSignature<Transform3D>();
		AddComponentSignature<RigidBody3D>();
	}

	void OnUpdate() {
		for (auto entity : entities) {
			auto& transform = FuseOrbit3D::Manager.GetComponent<Transform3D>(entity);
			auto& rigidbody = FuseOrbit3D::Manager.GetComponent<RigidBody3D>(entity);

			rigidbody.Accelaration = GRAVITY * rigidbody.GravityScale;
			transform.Position -= rigidbody.Velocity * rigidbody.Speed * FuseOrbit3D::Core.DeltaTime();
		}
	}
};
