#pragma once

#include "Core/ECS/Base/BaseComponent.h"
enum GuizmoMode { NONE, TRANSLATE, ROTATE, SCALE };

struct Gizmo3D : public ECS::BaseComponent {
	Gizmo3D() = default;
	~Gizmo3D() = default;
	GuizmoMode Mode = NONE;
};

