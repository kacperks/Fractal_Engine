#pragma once

#include "pch.h"

class PhysicsBody {
public:
	PhysicsBody() = default;
	PhysicsBody(const Vec3& pos, const Vec3& rot, float _radius) {
		_position = pos;
		_old_position = pos;
		_rotation = rot;
		_old_rotation = rot;
	}

	PhysicsBody operator=(PhysicsBody other) const;

	void UpdatePhysics();

	Vec3 GetPosition() { return _position; }
	Vec3 GetRotation() { return _rotation; }

	Vec3 GetOldPosition() { return _old_position; }
	Vec3 GetOldRotation() { return _old_rotation; }

	RigidBody GetRb() { return rb; }
	void SetRb(RigidBody other) { rb = other; }

private:
	RigidBody rb;
	Vec3 _position;
	Vec3 _rotation;
	Vec3 _old_rotation;
	Vec3 _old_position;
	uint8_t _moving;
};