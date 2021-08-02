#pragma once

#include "pch.h"

class PhysicsBody {
public:
	PhysicsBody() = default;
	PhysicsBody(const Vec3& pos, const Vec3& rot, float _radius) {
		_position = pos;
		_old_position = pos;
		pressure = 0.0f;
		radius = _radius;
		_rotation = rot;
		_old_rotation = rot;
	}

	virtual ~PhysicsBody();
	PhysicsBody operator=(PhysicsBody other) const;

	void UpdatePhysics();

	float radius;
	float pressure;
	float inertia;
	float move_acc;

private:
	Vec3 _position;
	Vec3 _rotation;
	Vec3 _old_rotation;
	Vec3 _old_position;
	uint8_t _moving;
};