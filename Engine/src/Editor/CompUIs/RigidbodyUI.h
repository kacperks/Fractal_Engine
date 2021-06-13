#pragma once

#include "pch.h"
#include "../UiLayer.h"
#include "Core/Engine.h"
#include "Events/EventSystem.h"

#include "Vendor/IMGUI/imgui_internal.h"
#include "Vendor/IMGUI/imgui_impl_glfw.h"
#include "Vendor/IMGUI/imgui_impl_opengl3.h"

#include "Core/ECS/Base/Entity.h"
#include "Serializer/XMLSerializer.h"

#include "DirectLightUI.h"
#include "PointLightUI.h"
#include "TransformUI.h"
#include "NameTagUI.h"
#include "MeshUI.h"

#include <fstream>

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
			ImGui::PushStyleColor(ImGuiCol_FrameBg, DARK);
			ImGui::PushStyleVar(ImGuiStyleVar_FramePadding, ImVec2(3, 3));
			ImGui::BeginChildFrame(ImGui::GetID("RB"), ImVec2(0, 55));
			ImGui::Button("Mass");
			ImGui::SameLine();
			ImGui::DragFloat("##Mass", &rb->Mass, 1.0f, 0, 0, "%.1f");
			ImGui::Button("Gravity scale");
			ImGui::SameLine();
			ImGui::DragFloat("##Gs", &rb->GravityScale, 1.0f, 0, 0, "%.1f");
			ImGui::PopStyleColor();
			ImGui::PopStyleVar();
			ImGui::EndChildFrame();
		}

	}

private:
	char buf[20];
	RigidBody* rb;
};