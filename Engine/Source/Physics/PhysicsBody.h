#pragma once

#include "pch.h"
#include "Core/Components/Transform.h"

namespace fr::Physics {
	class PhysicsBody {
	public:
		PhysicsBody(Vec3& _Velocity, Vec3& _Force, float _Mass , Transform _t);
		PhysicsBody operator=(PhysicsBody other) const;

		void Integrate(float delta); 
		static void Test();

		float Mass;
		Vec3 Velocity;
		Vec3 Force;

		Transform transform;
	};
}
