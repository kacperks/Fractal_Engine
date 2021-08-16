#pragma once

#include "Math/Vector3.h"
#include "SphereCollider.h"
#include "PlaneCollider.h"

struct CollisionPoints {
	Vec3 A;
	Vec3 B;
	Vec3 Normal = A.Normalized() + B.Normalized();
	float Depth = A.Lenght() + B.Lenght();
	bool HasCollision;
};


struct Collider {
	virtual CollisionPoints TestCollision(
		Transform transform,
		Collider collider,
		Transform colliderTransform) const = 0;

	virtual CollisionPoints TestCollision(
		Transform transform,
		SphereCollider sphere,
		Transform sphereTransform) const = 0;

	virtual CollisionPoints TestCollision(
		Transform transform,
		PlaneCollider plane,
		Transform planeTransform) const = 0;
};
