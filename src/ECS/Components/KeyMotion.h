#pragma once

#include "ECS/Core/BaseComponent.h"

enum class AxisType { ARROWS = 0, ADSW = 1, ADSWQE = 2, NUMERIC_ARROWS = 3 };

struct KeyMotion : public ECS::BaseComponent {
	KeyMotion(AxisType axis=AxisType::ADSWQE, float speed = 5.0f): Speed(speed), Axis(axis) { }
	AxisType Axis;
	float Speed;
};
