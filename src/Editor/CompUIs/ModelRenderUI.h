#pragma once

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
#include "../Text/EditorT.h"

#include "ECS/Components/CsScript.h"

#include <fstream>

#ifdef FRACTAL_WINDOWS
#include <windows.h>
#endif // FRACTAL_WINDOWS

#ifdef FRACTAL_LINUX
#include <bits/stdc++.h>
#endif

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