#pragma once

#include "Scene/BaseComponent.h"

#define RB_STATIC 0
#define RB_DYNAMIC 1

struct RigidBody : public ECS::BaseComponent {
	RigidBody() = default;
	~RigidBody() = default;
	
	int type = RB_DYNAMIC;

	FRfloat Mass = 1.000f;
	FRfloat LinearDrag = 0.000f;
	FRfloat AngularDrag = 0.050f;

	bool Gravity = true;
	bool IsKinematic = false;
};
