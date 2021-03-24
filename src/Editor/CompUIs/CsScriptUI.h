#pragma once

#include "CompUI.h"
#include "../../ECS/Components/EntityName.h"

class CsScriptUI : public CompUI {

public:
	NameTagUI(): buffer(), eName(nullptr) {}

	void Init(ECS::EntityID entity) override {
		isVisible = false;
		if (ECS::Manager.HasComponent<CsScript>(entity)) {
			script = &ECS::Manager.GetComponent<CsScript>(entity);
			isVisible = true;
		}
	}

	void Show() override {	

		if (ImGui::CollapsingHeader("CS Scripts")) {
			ImGui::SetCurrentFont(ImGui::GetIO().Fonts->Fonts[1]);
			ImGui::PushStyleVar(ImGuiStyleVar_FramePadding, FRAME_PADDING);
			ImGui::PushStyleColor(ImGuiCol_FrameBg, DARK);

			ImGui::BeginChildFrame(ImGui::GetID("scriptsframe"), ImVec2(0, 35));
			ImGui::PopStyleVar();
			ImGui::PopStyleColor();
			{
				ImGui::PushStyleVar(ImGuiStyleVar_FramePadding, ImVec2(3, 3));
				strcpy_s(buffer, DLLpath->Value.c_str());
				if(ImGui::InputText("FileName", buffer, IM_ARRAYSIZE(buffer))) {
					DLLpath->Value = std::string(buffer);
				}
				ImGui::PopStyleVar();
			}
			ImGui::EndChildFrame();
			ImGui::SetCurrentFont(ImGui::GetIO().Fonts->Fonts[0]);
		}
	}

private:
	CsScript script;
	char buffer[20];
	std::string ClassName;
	std::string DLLpath;
};