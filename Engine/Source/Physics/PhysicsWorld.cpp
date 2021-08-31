#include "pch.h"
#include "PhysicsWorld.h"

namespace fr::Physics {
	void PhysicsWorld::AddObject(PhysicsBody* Body) {
		m_objs.push_back(Body);
	}

	void PhysicsWorld::Step() {
		for (PhysicsBody* obj : m_objs) { /*...*/ }

	}
}