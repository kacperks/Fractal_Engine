#pragma once

#include "Collider.h"


class PlaneCollider : public Collider
{
public:
	PlaneCollider() = default;
	~PlaneCollider() = default;
	Vec3 Plane;
	float Distance;

	CollisionPoints TestCollision(Transform transform, Collider collider, Transform colliderTransform);
	CollisionPoints TestCollision(Transform transform, SphereCollider sphere, Transform sphereTransform);
	CollisionPoints TestCollision(Transform transform, PlaneCollider plane, Transform planeTransform);
};
