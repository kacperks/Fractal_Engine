#pragma once

#include "pch.h"
#include "../UiLayer.h"
#include "Core/Engine.h"
#include "Events/EventSystem.h"

#include "VendorE/IMGUI/imgui_internal.h"
#include "VendorE/IMGUI/imgui_impl_glfw.h"
#include "VendorE/IMGUI/imgui_impl_opengl3.h"

#include "Scene/Entity.h"
#include "Scene/SceneSerializer.h"

#include "DirectLightUI.h"
#include "PointLightUI.h"
#include "TransformUI.h"
#include "NameTagUI.h"
#include "MeshUI.h"


#include <fstream>

class ModelCompUI : public CompUI {
public:
	void Init(ECS::EntityID entity) override {
		isVisible = false;
		if (ECS::Manager.HasComponent<ModelRenderer>(entity)) {
			model = &ECS::Manager.GetComponent<ModelRenderer>(entity);
			isVisible = true;
		}
	}
	void Show() override {
		if (ImGui::CollapsingHeader("Model Renderer")) {
			strcpy_s(buf, model->Name.c_str());
			if (ImGui::InputText("Model Name", buf, IM_ARRAYSIZE(buf))) {
				model->Name = std::string(buf);
			}
			ImGui::SameLine();
			if (ImGui::Button("OK")) {
				model->ReFresh();
			}
		}
	}

private:
	char buf[20];
	ModelRenderer* model;
};