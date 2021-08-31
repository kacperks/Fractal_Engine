#pragma once

#include "Collider.h"

namespace fr::Physics {
	class SphereCollider : Collider {
	public:
		SphereCollider(const Vec3& center, float radius) : Collider(FR_PHYSICS_COLLIDER_TYPE_SPHERE),_center(center), _radius(radius) {}
		IntersectData IntersectSphereCollider(SphereCollider& other);
		virtual void Transform(Vec3& translation);
		static void Test();

		Vec3  _center;
		float _radius;
	};
}