#pragma once

#include "pch.h"
#include "Core/Components/Transform.h"
#include "Collider.h"

namespace fr::Physics {
	class PhysicsBody {
	public:
		PhysicsBody(Collider* _collider, const Math::Vec3& velocity) : Collider(_collider), Velocity(velocity) {}
		PhysicsBody(Collider* _collider, Math::Vec3& _Velocity, Math::Vec3& _Force, float _Mass, Math::Vec3 _Position) : Mass(_Mass), Position(_Position), Force(_Force), Velocity(_Velocity) , Collider(_collider) {}
		PhysicsBody operator=(PhysicsBody other) const;

		void Inte(); 
		static void Test();

		Collider* GetCollider() {
			Math::Vec3 translation = Position - OldPosition;
			OldPosition = Position;
			Collider->Transform(translation);
			return Collider;
		}

		float Mass;
		Math::Vec3 Velocity;
		Math::Vec3 Force;
		Math::Vec3 Position;
		Math::Vec3 OldPosition;

	private:
		Collider* Collider;
	};
}
