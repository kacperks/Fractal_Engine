#pragma once

#include "Collider.h"
#include "algo.h"

struct SphereCollider : public Collider
{
	Vec3 Center;
	float Radius;

	CollisionPoints TestCollision(Transform transform, Collider collider, Transform colliderTransform);
	CollisionPoints TestCollision(Transform transform, SphereCollider sphere, Transform sphereTransform);
	CollisionPoints TestCollision(Transform transform, PlaneCollider plane, Transform planeTransform);
};
