#pragma once

#include "Scene/BaseComponent.h"

struct KeyMotion : public ECS::BaseComponent {
	KeyMotion() = default;
	float Speed = 5.0f;
};
