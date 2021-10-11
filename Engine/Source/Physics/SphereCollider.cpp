#include "pch.h"
#include "SphereCollider.h"

namespace fr::Physics {
	IntersectData SphereCollider::IntersectSphereCollider(SphereCollider& other)
	{
		float radiusDistance = _radius + other._radius;
		Vec3 direction = (other._center - _center);
		float centerDistance = direction.Length();
		direction /= centerDistance;
		float distance = centerDistance - radiusDistance;
		return IntersectData(distance < 0, direction* distance);
	}
}