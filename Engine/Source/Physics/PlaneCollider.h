#pragma once

#include "Collider.h"

struct PlaneCollider : Collider {
	Vec3 Plane;
	float Distance;

	CollisionPoints TestCollision1(Transform transform, Collider collider, Transform colliderTransform);
	CollisionPoints TestCollision(Transform transform, SphereCollider sphere, Transform sphereTransform);
	CollisionPoints TestCollision(Transform transform, PlaneCollider plane, Transform planeTransform);
};
