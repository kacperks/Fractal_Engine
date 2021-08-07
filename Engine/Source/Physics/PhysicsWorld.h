#pragma once

#include "PhysicsBody.h"

class PhysicsWorld {
public:

	void AddObject   (PhysicsBody* Body);
	void RemoveObject(PhysicsBody* body);

	void Step(float dt);
private:
	std::vector<PhysicsBody*> m_bodies;
	Vec3 gravity = Vec3(0, -9, 0);
};