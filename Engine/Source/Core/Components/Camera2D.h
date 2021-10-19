#pragma once

#include "Math/Vector2.h"
#include "Renderer/Shader.h"
#include "Scene/BaseComponent.h"

struct Camera2D : public ECS::BaseComponent {
    fr::Vec3 Position;
    fr::Vec3 Scale;
    fr::Vec3 Rotation;


};