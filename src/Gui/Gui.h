#pragma once

#include <map>
#include <tuple>
#include <vector>
#include <algorithm>
#include <filesystem>

#include "../fractal.hpp"

// User Controls
#include "Controls/NameUserControl.h"
#include "Controls/LightUserControl.h"
#include "Controls/MaterialUserControl.h"
#include "Controls/TransformUserControl.h"

std::pair<bool, uint32_t> DirectoryTreeViewRecursive(const std::filesystem::path& path, uint32_t* count, int* selection_mask) {

	ImGuiTreeNodeFlags base_flags = /* ImGuiTreeNodeFlags_OpenOnArrow | ImGuiTreeNodeFlags_OpenOnDoubleClick |*/ ImGuiTreeNodeFlags_SpanAvailWidth |
		ImGuiTreeNodeFlags_SpanFullWidth;

	bool any_node_clicked = false;
	uint32_t node_clicked = 0;

	for (const auto& entry : std::filesystem::directory_iterator(path))
	{
		ImGuiTreeNodeFlags node_flags = base_flags;
		const bool is_selected = (*selection_mask & *count) != 0;
		if (is_selected)
			node_flags |= ImGuiTreeNodeFlags_Selected;

		std::string name = entry.path().string();

		auto lastSlash = name.find_last_of("/\\");
		lastSlash = (lastSlash == std::string::npos) ? 0 : lastSlash + 1;
		name = name.substr(lastSlash, name.size() - lastSlash);

		bool entryIsFile = !std::filesystem::is_directory(entry.path());
		if (entryIsFile)
			node_flags |= ImGuiTreeNodeFlags_Leaf | ImGuiTreeNodeFlags_NoTreePushOnOpen;

		bool node_open = ImGui::TreeNodeEx((void*)(intptr_t)(*count), node_flags, name.c_str());

		if (ImGui::IsItemClicked())
		{
			node_clicked = *count;
			any_node_clicked = true;
		}

		(*count)--;

		if (!entryIsFile)
		{
			if (node_open)
			{
				auto clickState = DirectoryTreeViewRecursive(entry.path(), count, selection_mask);

				if (!any_node_clicked)
				{
					any_node_clicked = clickState.first;
					node_clicked = clickState.second;
				}

				ImGui::TreePop();
			}
			else
			{
				for (const auto& e : std::filesystem::recursive_directory_iterator(entry.path()))
					(*count)--;
			}
		}
	}

	return { any_node_clicked, node_clicked };
}

void OnImGui(std::string directoryPath)
{
	Widget::Window::Begin("Resources");
	{
		Widget::Frame::Begin("ResourcesBody"); 
		{
			uint32_t count = 0;
			for (const auto& entry : std::filesystem::recursive_directory_iterator(directoryPath))
				count++;

			static int selection_mask = 0;

			auto clickState = DirectoryTreeViewRecursive(directoryPath, &count, &selection_mask);

			Widget::Frame::End();
		}

	}
	Widget::Window::End();


}

class Gui {

public:
	static Gui& Get() {
		static Gui control;
		return control;
	}

	void Display() {
		ImGui_ImplOpenGL3_NewFrame();
		ImGui_ImplGlfw_NewFrame();
		ImGui::NewFrame();
		{			
			Dockspace();			
			Viewport();
			Components();
			Entities();
			Resources();
			Console();
			//ImGui::ShowDemoWindow();
		}
		ImGui::Render();
		ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
		GLFWwindow* backup_current_context = glfwGetCurrentContext();
		ImGui::UpdatePlatformWindows();
		ImGui::RenderPlatformWindowsDefault();
		glfwMakeContextCurrent(backup_current_context);		
	}

	void Initialize() {
		IMGUI_CHECKVERSION();
		ImGui::CreateContext();
		ImGuiIO& IO = ImGui::GetIO(); (void)IO;

		SetGuiStyle();
		IO.ConfigFlags |= ImGuiConfigFlags_DockingEnable;
		IO.ConfigFlags |= ImGuiConfigFlags_ViewportsEnable;
		IO.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;
		IO.Fonts->AddFontFromFileTTF("Resource/Fonts/Roboto-Medium.ttf", 14.0f);

		ImGui_ImplOpenGL3_Init("#version 330");
		ImGui_ImplGlfw_InitForOpenGL(&FuseOrbit3D::Core.Window(), true);

		window_flags = ImGuiWindowFlags_MenuBar | ImGuiWindowFlags_NoDocking | ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoCollapse |
			ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoBringToFrontOnFocus | ImGuiWindowFlags_NoNavFocus | ImGuiWindowFlags_NoBackground;
		
		lastSelectedObj = -1;
		selectedObj = (entities.size() > 1) ? entities.front() : -1;

		user_controls.push_back(new NameUserControl());
		user_controls.push_back(new TagUserControl());
		user_controls.push_back(new TransformUserControl());
		user_controls.push_back(new MaterialUserControl());
		user_controls.push_back(new LightUserControl());
	}

	void AddExistingEntity(int entity) {
		entities.push_back(entity);
	}

private:
	void MenuBar() {		
		if (ImGui::BeginMenuBar()) {
			if (ImGui::BeginMenu("File")){				
				if (ImGui::MenuItem("New", "Ctrl+N")) {}
				if (ImGui::MenuItem("Open", "Ctrl+O")) {}
				if (ImGui::MenuItem("Save", "Ctrl+S")) {}
				if (ImGui::MenuItem("Save As..")) {}
				ImGui::EndMenu();
			}
			if (ImGui::BeginMenu("Editor")){
				if (ImGui::MenuItem("Undo", "CTRL+Z")) {}
				if (ImGui::MenuItem("Redo", "CTRL+Y", false, false)) {}  // Disabled item
				ImGui::Separator();
				if (ImGui::MenuItem("Cut", "CTRL+X")) {}
				if (ImGui::MenuItem("Copy", "CTRL+C")) {}
				if (ImGui::MenuItem("Paste", "CTRL+V")) {}
				ImGui::EndMenu();
			}
			if (ImGui::BeginMenu("Settings")) {
				if (ImGui::MenuItem("Customize", "Ctrl+T")) {}		
				ImGui::EndMenu();
			}
			if (ImGui::BeginMenu("Help")) {
				if (ImGui::MenuItem("View Help", "Ctrl+H")) {}
				if (ImGui::MenuItem("About Soft3D")) {}
				ImGui::EndMenu();
			}

			ImGui::EndMenuBar();
		}		
	}

	void Viewport() {		
		Widget::Window::Begin("Scene", 5.0f, 8.0f, ImGuiWindowFlags_NoDecoration);
		{
			Widget::Frame::Begin("MainToolbar", 35.0f, 5.0f);
			{
				//ImGui::Dummy(ImVec2(25.0f, 25.0f));
				if (Widget::ToolButton::Display(UI_ASSETS.Icon("view"))) {

				}

				ImGui::SameLine();
				if (Widget::ToolButton::Display(UI_ASSETS.Icon("move"))) {

				}

				ImGui::SameLine();
				if (Widget::ToolButton::Display(UI_ASSETS.Icon("rotate"))) {

				}

				ImGui::SameLine();
				if (Widget::ToolButton::Display(UI_ASSETS.Icon("play"))) {
					FuseOrbit3D::Core.mode = OperationMode::GAME_MODE;
				}
				Widget::Frame::End();
			}
			
			Widget::Frame::Begin("GAME", 0.0f, 0.0f);
			{
				auto size = ImGui::GetWindowSize();
				ImGui::Image((ImTextureID)RESOURCE.GetTex2D("SceneFBO"), size, ImVec2(0, 1), ImVec2(1, 0));
				Widget::Frame::End();
			}

			Widget::Window::End();
		}
	}

	void Entities() {	
		
		Widget::Window::Begin("Entities");
		{
			Widget::Frame::Begin("EntityToolbar", 30.0f, 5.0f);
			{
				if (Widget::ToolButton::Display(UI_ASSETS.Icon("add"), 20.0f)) {
					AddNewEntity();
				}

				ImGui::SameLine();
				if (Widget::ToolButton::Display(UI_ASSETS.Icon("minus"), 20.0f)) {
					RemoveEntity();
				}

				ImGui::SameLine();
				if (Widget::ToolButton::Display(UI_ASSETS.Icon("up"), 20.0f)) {
					MoveEntityUp();
				}

				ImGui::SameLine();
				if (Widget::ToolButton::Display(UI_ASSETS.Icon("down"), 20.0f)) {
					MoveEntityDown();
				}

				Widget::Frame::End();
			}

			Widget::Frame::Begin("Entities");
			for (const auto& entity : entities) {
				lastSelectedObj = selectedObj;
				const auto& name = FuseOrbit3D::Manager.GetComponent<Name>(entity);

				objIcon = entityIcon;

				if (FuseOrbit3D::Manager.HasComponent<Light>(entity)) {
					objIcon = lightIcon;
				}
				if (FuseOrbit3D::Manager.HasComponent<Camera>(entity)) {
					objIcon = cameraIcon;
				}

				selectedObj = Widget::EntitySelectable::Display(name.Value.c_str(), entity, selectedObj, objIcon);
				if (selectedObj != -1 && !FuseOrbit3D::Manager.HasComponent<KeyMotion>(selectedObj)) {
					FuseOrbit3D::Manager.AddComponent<KeyMotion>(selectedObj);
				}
				if (lastSelectedObj != -1 && lastSelectedObj != selectedObj && FuseOrbit3D::Manager.HasComponent<KeyMotion>(lastSelectedObj)) {
					FuseOrbit3D::Manager.RemoveComponent<KeyMotion>(lastSelectedObj);
				}
			}
			Widget::Frame::End();
		}
		Widget::Window::End();
	}

	void Components() {		
		Widget::Window::Begin("Components");
		{
			Widget::Frame::Begin("EntityToolbar", 30.0f, 5.0f);
			{
				if (Widget::ToolButton::Display(UI_ASSETS.Icon("add"), 20.0f)) {
					AddComponent();
				}

				ImGui::SameLine();
				if (Widget::ToolButton::Display(UI_ASSETS.Icon("minus"), 20.0f)) {
					RemoveComponent();
				}
				Widget::Frame::End();
			}

			if (selectedObj > -1) {
				for (auto control : user_controls) {
					control->Display(selectedObj);
				}
			}
			Widget::Window::End();
		}
	}

	void Console() {
		Widget::Window::Begin("Console");
		{
			Widget::Frame::Begin("ConsoleBody");
			Widget::Frame::End();
		}
		Widget::Window::End();
	}

	void Resources() {

		OnImGui("C:/Users/fpouh/Desktop/SOFT_ENGINE_3D/SOFT_ENGINE_3D/Resource");

		/*Widget::Window::Begin("Resources");
		{
			Widget::Frame::Begin("ResourcesBody");
			Widget::Frame::End();
		}
		Widget::Window::End();*/
	}

	void Dockspace() {		
		ImGuiViewport* viewport = ImGui::GetMainViewport();
		ImGui::SetNextWindowPos(viewport->Pos);
		ImGui::SetNextWindowSize(viewport->Size);
		ImGui::SetNextWindowViewport(viewport->ID);
		ImGui::PushStyleVar(ImGuiStyleVar_WindowRounding, 0.0f);
		ImGui::PushStyleVar(ImGuiStyleVar_WindowBorderSize, 0.0f);
		ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2(0.0f, 0.0f));

		ImGui::Begin("Dockspace", nullptr, window_flags);
		{
			ImGuiID dockID = ImGui::GetID("Dockspace");
			ImGui::DockSpace(dockID, ImVec2(0.0f, 0.0f), ImGuiDockNodeFlags_PassthruCentralNode);
		}

		MenuBar();

		ImGui::End();
		ImGui::PopStyleVar(3);
	}		

	void SetGuiStyle() {
		ImGui::StyleColorsDark();
		ImGuiStyle& style = ImGui::GetStyle();
		style.ItemSpacing = ImVec2(5, 5);
		style.FramePadding = ImVec2(5, 10);
		style.WindowRounding = 0;
		style.ItemInnerSpacing = ImVec2(5, 5);
		style.WindowBorderSize = 0;
		style.WindowPadding = ImVec2(10, 10);
		style.ScrollbarSize = 12;
		style.GrabMinSize = 10;
		style.GrabRounding = 2;
		style.FrameBorderSize = 1;
		style.FrameRounding = 2;
		style.TabBorderSize = 1;
		style.TabRounding = 0;
		style.ChildRounding = 0;		
		style.ChildBorderSize = 0;		
		//style.DisplaySafeAreaPadding = ImVec2(5, 5);

		// colors
		style.Colors[ImGuiCol_WindowBg] = ImVec4(0.1f, 0.1f, 0.1f, 1.0f);
		style.Colors[ImGuiCol_ChildBg] = ImVec4(0.1f, 0.1f, 0.1f, 1.0f);
		style.Colors[ImGuiCol_TitleBg] = ImVec4(0.13f, 0.13f, 0.13f, 1.0f);
		style.Colors[ImGuiCol_Button] = ImVec4(0.0f, 0.0f, 0.0f, 0.0f);
		style.Colors[ImGuiCol_Border] = ImVec4(0.23f, 0.23f, 0.23f, 1.0f);

		//style.Colors[ImGuiCol_FrameBg] = ImVec4(0.2f, 0.2f, 0.2f, 1.0f);

		//style.Colors[ImGuiCol_Text] = ImVec4(0.8f, 0.8f, 0.8f, 1.0f);
		////style.Colors[ImGuiCol_FrameBgActive] = ImVec4(0.0f, 0.48f, 0.8f, 1.0f);
		//style.Colors[ImGuiCol_TitleBgActive] = ImVec4(0.14f, 0.26f, 0.42f, 1.0f);
		//style.Colors[ImGuiCol_TitleBgCollapsed] = ImVec4(0.14f, 0.26f, 0.42f, 1.0f);
		//style.Colors[ImGuiCol_CheckMark] = ImVec4(00.0f, 0.48f, 0.8f, 1.0f);
		////style.Colors[ImGuiCol_Separator] = ImVec4(0.25f, 0.25f, 0.27f, 1.0f);
		//style.Colors[ImGuiCol_SliderGrab] = ImVec4(0.42f, 0.42f, 0.42f, 1.0f);
		//style.Colors[ImGuiCol_SliderGrabActive] = ImVec4(0.62f, 0.62f, 0.62f, 1.0f);
		//style.Colors[ImGuiCol_Tab] = ImVec4(0.18f, 0.18f, 0.19f, 1.0f);
		//style.Colors[ImGuiCol_TabActive] = ImVec4(0.0f, 0.48f, 0.8f, 1.0f);
		//style.Colors[ImGuiCol_TabHovered] = ImVec4(0.18f, 0.18f, 0.19f, 1.0f);
		//style.Colors[ImGuiCol_ScrollbarGrabActive] = ImVec4(0.25f, 0.25f, 0.27f, 1.0f);
		//style.Colors[ImGuiCol_MenuBarBg] = ImVec4(0.14f, 0.26f, 0.42f, 1.0f);
	}

	// Actions methods

	void MoveEntityUp() {
		auto it = std::find(entities.begin(), entities.end(), selectedObj);
		if (it == entities.end()) { return; }

		int pos = std::distance(entities.begin(), it);

		if (pos > 0) {
			int prev = pos - 1;
			int temp = entities[prev];
			entities[prev] = *it;
			entities[pos] = temp;
		}
	}

	void MoveEntityDown() {
		auto it = std::find(entities.begin(), entities.end(), selectedObj);
		if (it == entities.end()) { return; }
		int pos = std::distance(entities.begin(), it);
		if (pos < entities.size() - 1) {
			int temp = entities[pos + 1];
			entities[pos + 1] = *it;
			entities[pos] = temp;
		}
	}

	void AddNewEntity() {
		ECS::Entity entity = FuseOrbit3D::Manager.AddEntity();
		entity.AddComponent<Transform3D>();
		entity.AddComponent<Material>();
		entity.AddComponent<Name>("Entity" + std::to_string(entity.GetHandle()));
		entities.push_back(entity.GetHandle());
		selectedObj = entity.GetHandle();
	}

	void RemoveEntity() {
		if (selectedObj > -1) {
			FuseOrbit3D::Manager.DestroyEntity(selectedObj);
			auto it = std::find(entities.begin(), entities.end(), selectedObj);
			if (it != entities.end()) {
				entities.erase(it);
			}
			selectedObj = (entities.size() > 1) ? entities.back() : -1;
		}
	}

	void AddComponent() {
		if (selectedObj > -1) {
			FuseOrbit3D::Manager.AddComponent<Tag>(selectedObj);
		}
	}

	void RemoveComponent() {
		if (selectedObj > -1) {
			FuseOrbit3D::Manager.RemoveComponent<Tag>(selectedObj);
		}
	}

private:
	int selectedObj;
	int lastSelectedObj;

	ImTextureID entityIcon = UI_ASSETS.Icon("entity");
	ImTextureID cameraIcon = UI_ASSETS.Icon("camera");
	ImTextureID lightIcon = UI_ASSETS.Icon("light");
	ImTextureID objIcon = entityIcon;

	ImGuiWindowFlags window_flags;

	std::vector<int> entities;
	std::vector<UserControl*> user_controls;
};

static Gui& GUI = Gui::Get();
