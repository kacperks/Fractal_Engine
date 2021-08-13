#pragma once

#include "pch.h"
#include "../UiLayer.h"
#include "Core/Engine.h"
#include "Events/EventSystem.h"

#include "Vendor/IMGUI/imgui_internal.h"
#include "Vendor/IMGUI/imgui_impl_glfw.h"
#include "Vendor/IMGUI/imgui_impl_opengl3.h"

#include "Scene/Entity.h"
#include "Scene/XMLSerializer.h"

#include "DirectLightUI.h"
#include "PointLightUI.h"
#include "TransformUI.h"
#include "NameTagUI.h"
#include "MeshUI.h"

#include <fstream>

class CamUI : public CompUI {
public:
	void Init(ECS::EntityID entity) override {
		isVisible = false;
		if (ECS::Manager.HasComponent<Camera>(entity)) {
			rb = &ECS::Manager.GetComponent<Camera>(entity);
			isVisible = true;
		}
	}
	void Show() override {
		if (ImGui::CollapsingHeader("Camera 3D")) {

			ImGui::PushStyleColor(ImGuiCol_FrameBg, ImVec4(0.21f, 0.22f, 0.23, 1.0f));
			ImGui::PushStyleColor(ImGuiCol_Button, BLUE);

			ImGui::PushStyleVar(ImGuiStyleVar_FramePadding, ImVec2(3, 3));

			ImGui::BeginChildFrame(ImGui::GetID("CamUIFrame"), ImVec2(0, 79));

			ImGui::Button("FOV");
			ImGui::SameLine();
			ImGui::DragFloat("##FOV", &rb->FieldOfView, 1.0f, 0, 0, "%.1f");

			ImGui::Button("zNear");
			ImGui::SameLine();
			ImGui::DragFloat("##zNear", &rb->zNear, 1.0f, 0, 0, "%.1f");

			ImGui::Button("zFar");
			ImGui::SameLine();
			ImGui::DragFloat("##zFar", &rb->zFar, 1.0f, 0, 0, "%.1f");


			ImGui::PopStyleVar();
			ImGui::PopStyleColor();
			ImGui::PopStyleColor();
			ImGui::EndChildFrame();
		}
	}

private:
	char buf[20];
	Camera* rb;
};