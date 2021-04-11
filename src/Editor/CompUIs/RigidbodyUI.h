#pragma once

#include "../../fractal.hpp"
#include "../UiLayer.h"
#include "../../Engine/Engine.h"
#include "../../Events/EventSystem.h"

#include "../../vendor/IMGUI/imgui_internal.h"
#include "../../vendor/IMGUI/imgui_impl_glfw.h"
#include "../../vendor/IMGUI/imgui_impl_opengl3.h"

#include "../../ECS/Base/Entity.h"
#include "../../Serializer/XMLSerializer.h"

#include "DirectLightUI.h"
#include "PointLightUI.h"
#include "TransformUI.h"
#include "NameTagUI.h"
#include "MeshUI.h"

#include "../../ECS/Components/CsScript.h"

#include <fstream>

#ifdef FRACTAL_WINDOWS
#include <windows.h>
#endif // FRACTAL_WINDOWS

#ifdef FRACTAL_LINUX
#include <bits/stdc++.h>
#endif

class RBUI : public CompUI {
public:
	void Init(ECS::EntityID entity) override {
		isVisible = false;
		if (ECS::Manager.HasComponent<RigidBody>(entity)) {
			rb = &ECS::Manager.GetComponent<RigidBody>(entity);
			isVisible = true;
		}
	}
	void Show() override {
		if (ImGui::CollapsingHeader("Rigidbody")) {
			ImGui::Button("Mass");
			ImGui::SameLine();
			ImGui::DragFloat("##Mass", &rb->Mass, 1.0f, 0, 0, "%.1f");
			ImGui::Button("Gravity scale");
			ImGui::SameLine();
			ImGui::DragFloat("##Gs", &rb->GravityScale, 1.0f, 0, 0, "%.1f");
		}
	}

private:
	char buf[20];
	RigidBody* rb;
};