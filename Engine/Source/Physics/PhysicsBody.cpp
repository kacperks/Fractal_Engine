#include "pch.h"

#include "PhysicsBody.h"

namespace fr::Physics {
	void PhysicsBody::Inte() {
		Position += Velocity * Timer.DeltaTime();
	}

	void PhysicsBody::Test() {

	}
}