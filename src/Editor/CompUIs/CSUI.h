#pragma once

#include "../../fractal.hpp"
#include "../UiLayer.h"
#include "../../Engine/Engine.h"
#include "../../Events/EventSystem.h"

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
			if (ImGui::InputText("Name", buf, IM_ARRAYSIZE(buf))) {}
			if (ImGui::Button("Load File")) { script->AssemblyPath = "Resource/Scripts/" + std::string(buf); }
			ImGui::SameLine();
			if (ImGui::Button("Clear")) { for (int i = 0; i < 20; i++) { buf[i] = 0; } }
			ImGui::SameLine();
			if (ImGui::Button("Edit Script")) { system("code Resource/Scripts/."); }
		}
	}
	private:
		CsScript* script;
		char buf[20];
};

