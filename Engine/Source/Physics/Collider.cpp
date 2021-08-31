#include "pch.h"
#include "Collider.h"
#include "SphereCollider.h"

namespace fr::Physics {
	IntersectData Collider::Intersect(const Collider& other) const
	{
		if (_type == FR_PHYSICS_COLLIDER_TYPE_SPHERE && other.GetType() == FR_PHYSICS_COLLIDER_TYPE_SPHERE) {
			SphereCollider* self = (SphereCollider*)this;
			return self->IntersectSphereCollider((SphereCollider&)other);
		}

		FR_ERROR("Collisions Error!");
		exit(1);

		return IntersectData(false, Vec3(0.0f, 0.0f , 0.0f));
	}
}