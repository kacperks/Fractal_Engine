#pragma once

#include "Collider.h"

namespace fr::Physics {
	class SphereCollider : Collider {
	public:
		SphereCollider(const Math::Vec3& center, float radius) : Collider(FR_PHYSICS_COLLIDER_TYPE_SPHERE),_center(center), _radius(radius) {}
		IntersectData IntersectSphereCollider(SphereCollider& other);
		virtual void Transform(Math::Vec3& translation);
		static void Test();

		Math::Vec3  _center;
		float _radius;
	};
}