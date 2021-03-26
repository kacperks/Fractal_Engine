#pragma once

#include "CompUI.h"
#include "Resource/Resource.h"
#include "ECS/Components/CsScript.h"

class CsCompUI : CompUI {
	public:
		std::string ValueDLL;
		std::string ValueClass;
		void Init(ECS::EntityID entity) override {
			isVisible = false;
			if (ECS::Manager.HasComponent<CsScript>(entity)) {
				script = &ECS::Manager.GetComponent<CsScript>(entity);
				isVisible = true;
			}
		}
		void Show() override {
			if (ImGui::CollapsingHeader("C# Script")) {
				ImGui::PushStyleVar(ImGuiStyleVar_FramePadding, FRAME_PADDING);
				ImGui::PushStyleColor(ImGuiCol_FrameBg, DARK);

				ImGui::BeginChildFrame(ImGui::GetID("csframe"), ImVec2(0, 75));
				ImGui::PopStyleVar();
				ImGui::PopStyleColor();
				{
					//if (ImGui::InputText("Class Name", buffer2, IM_ARRAYSIZE(buffer2))) {
					//	ValueClass = std::string(buffer2);
					//}
					if (ImGui::InputText("DLL path", buffer, IM_ARRAYSIZE(buffer))) {
						CsScript::AssemblyPath = std::string(buffer);
					}
				}
			}
		}
private:
	char buffer[20];
	CsScript* script;
};