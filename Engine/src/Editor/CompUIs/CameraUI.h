#pragma once

#ifndef FR_CAMERA_COMPONENT_UI
#define FR_CAMERA_COMPONENT_UI

#include "pch.h"
#include "../UiLayer.h"
#include "Engine/Engine.h"
#include "Events/EventSystem.h"

#include "Vendor/IMGUI/imgui_internal.h"
#include "Vendor/IMGUI/imgui_impl_glfw.h"
#include "Vendor/IMGUI/imgui_impl_opengl3.h"

#include "ECS/Base/Entity.h"
#include "Serializer/XMLSerializer.h"

#include "DirectLightUI.h"
#include "PointLightUI.h"
#include "TransformUI.h"
#include "NameTagUI.h"
#include "MeshUI.h"

#include "ECS/Components/CsScript.h"

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
			ImGui::Button("FOV");
			ImGui::SameLine();
			ImGui::DragFloat("##FOV", &rb->FieldOfView, 1.0f, 0, 0, "%.1f");
		}
	}

private:
	char buf[20];
	Camera* rb;
};

#endif 