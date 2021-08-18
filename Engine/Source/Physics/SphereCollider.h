#pragma once

#include "Collider.h"
#include "algo.h"

class SphereCollider : public Collider
{
public:
	SphereCollider() = default;
	~SphereCollider() = default;
	Vec3 Center;
	float Radius;

	virtual CollisionPoints TestCollision(Transform transform, Collider collider, Transform colliderTransform);
	virtual CollisionPoints TestCollision(Transform transform, SphereCollider sphere, Transform sphereTransform);
	virtual CollisionPoints TestCollision(Transform transform, PlaneCollider plane, Transform planeTransform);
};
