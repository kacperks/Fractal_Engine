#pragma once

#include "PhysicsBody.h"

namespace fr::Physics {
	class PhysicsWorld {
	private:
		std::vector<PhysicsBody*> m_objs;
		Math::Vec3 gravity = Math::Vec3(0, -9, 0);
	public:
		void AddObject(PhysicsBody* Body);
		void RemoveObject(PhysicsBody* body);

		void Step();
		void ResolveCollisions();

		PhysicsBody* GetObject(unsigned int index);
	};
}