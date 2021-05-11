#pragma once

#include "ECS/Base/BaseComponent.h"

struct KeyMotion : public ECS::BaseComponent {
	KeyMotion() = default;
	float Speed = 5.0f;
};
