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
		}
	}

private:
	char buf[20];
	ModelRenderer* model;
};