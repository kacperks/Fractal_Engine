#pragma once

#include "Collider.h"

/*
struct PlaneCollider : Collider {
	Vec3 Plane;
	float Distance;

	CollisionPoints TestCollision( const Transform* transform, const Collider* collider, const Transform* colliderTransform) {
		return collider->TestCollision(colliderTransform, this, transform);
	}

	CollisionPoints TestCollision( const Transform* transform, const SphereCollider* sphere, const Transform* sphereTransform) {
		return sphere->TestCollision(sphereTransform, this, transform);
	}

	CollisionPoints TestCollision(const Transform* transform, const PlaneCollider* plane, const Transform* planeTransform) {}
};
*/