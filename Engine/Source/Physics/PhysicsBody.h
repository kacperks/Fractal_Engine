#pragma once

#include "pch.h"
#include "Core/Components/Transform.h"
#include "Collider.h"

namespace fr::Physics {
	class PhysicsBody {
	public:
		PhysicsBody(Collider* _collider, const Vec3& velocity) : Collider(_collider), Velocity(velocity) {}
		PhysicsBody(Collider* _collider, Vec3& _Velocity, Vec3& _Force, float _Mass, Vec3 _Position) : Mass(_Mass), Position(_Position), Force(_Force), Velocity(_Velocity) , Collider(_collider) {}
		PhysicsBody operator=(PhysicsBody other) const;

		void Inte(); 
		static void Test();

		Collider* GetCollider() {
			Vec3 translation = Position - OldPosition;
			OldPosition = Position;
			Collider->Transform(translation);
			return Collider;
		}

		float Mass;
		Vec3 Velocity;
		Vec3 Force;
		Vec3 Position;
		Vec3 OldPosition;

	private:
		Collider* Collider;
	};
}
