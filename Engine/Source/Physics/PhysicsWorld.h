#pragma once

#include "PhysicsBody.h"

namespace fr::Physics {
	class PhysicsWorld {
	public:
		void AddObject(PhysicsBody* Body);
		void RemoveObject(PhysicsBody* body);

		void Step();
		void ResolveCollisions();

		PhysicsBody* GetObject(unsigned int index);

	private:
		std::vector<PhysicsBody*> m_objs;
		Vec3 gravity = Vec3(0, -9, 0);
	};
}