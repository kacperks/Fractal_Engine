#pragma once

#include "Math/Vector3.h"
#include "SphereCollider.h"
#include "PlaneCollider.h"

struct CollisionPoints {
	CollisionPoints() = default;
	~CollisionPoints() = default;

	Vec3 A;
	Vec3 B;
	Vec3 Normal = A.Normalized() + B.Normalized();
	float Depth = A.Lenght() + B.Lenght();
	bool HasCollision;
};


class Collider {
public:
	Collider() = default;
	~Collider() = default;

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
