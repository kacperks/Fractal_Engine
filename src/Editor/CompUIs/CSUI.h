#pragma once

#ifdef FRACTAL_CSHARP

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

#ifdef FRACTAL_WINDOWS
#include <windows.h>
#endif // FRACTAL_WINDOWS

#ifdef FRACTAL_LINUX
#include <bits/stdc++.h>
#endif

class CsScriptCompUI : public CompUI {
public:
	void Init(ECS::EntityID entity) override {
		isVisible = false;
		if (ECS::Manager.HasComponent<CsScript>(entity)) {
			script = &ECS::Manager.GetComponent<CsScript>(entity);
			isVisible = true;
		}
	}

	void Show() override {
		
		if (ImGui::CollapsingHeader("C# Script")) {
			//ImGui::SetCurrentFont(ImGui::GetIO().Fonts->Fonts[1]);
			ImGui::PushStyleVar(ImGuiStyleVar_FramePadding, FRAME_PADDING);
			ImGui::PushStyleColor(ImGuiCol_FrameBg, DARK);

			ImGui::BeginChildFrame(ImGui::GetID("RB"), ImVec2(0, 110));

			ImGui::PopStyleVar();
			ImGui::PopStyleColor();

			ImGui::PushStyleVar(ImGuiStyleVar_FramePadding, ImVec2(3, 3));

			if (ImGui::InputText("Script FileName", buf, IM_ARRAYSIZE(buf))) { script->AssemblyPath = "Resource/Scripts/" + std::string(buf); }

			if (ImGui::Button("Clear")) { script->AssemblyPath = ""; }

			ImGui::SameLine();

			if (ImGui::Button("Edit Script")) { system("code Resource/Scripts/."); }

			if (ImGui::InputText("Class Name", buf2, IM_ARRAYSIZE(buf2))) { script->ClassName = std::string(buf2); }

			if (ImGui::Button("Clear")) { script->ClassName = ""; }

			strcpy_s(buf, script->AssemblyPath.c_str());

			strcpy_s(buf2, script->ClassName.c_str());
			ImGui::PopStyleVar();
			ImGui::EndChildFrame();
		}
	}
	private:
		CsScript* script;
		char buf[40];
		char buf2[20];
};


#endif