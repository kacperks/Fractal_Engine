#include "../fractal.hpp"
#include "UiLayer.h"
#include "../Engine/Engine.h"
#include "../Events/EventSystem.h"

#include "../vendor/imgui/imgui_internal.h"
#include "../vendor/imgui/imgui_impl_glfw.h"
#include "../vendor/imgui/imgui_impl_opengl3.h"

#include "../ECS/Base/Entity.h"
#include "Serializer/XMLSerializer.h"

#include "CompUIs/DirectLightUI.h"
#include "CompUIs/PointLightUI.h"
#include "CompUIs/TransformUI.h"
#include "CompUIs/NameTagUI.h"
#include "CompUIs/MeshUI.h"

#include "CompUIs/CSUI.h"
#include "CompUIs/ModelRenderUI.h"
#include "CompUIs/RigidbodyUI.h"
#include "CompUIs/CameraUI.h"


#include <fstream>

#ifdef FRACTAL_WINDOWS
	#include <windows.h>
#endif // FRACTAL_WINDOWS

#ifdef FRACTAL_LINUX
	#include <bits/stdc++.h>
#endif

namespace fr {
		char buf[20];
	std::string console = "Fractal Debug Console";
	const ImVec4 dark = ImVec4(0.17f, 0.17f, 0.17f, 1.0f);
	static const char* names[] = { "Camera", "RigidBody", "MeshRenderer",
		"ModelRenderer", "SpriteRenderer", "Directional Light", "Point Light", "Spot Light", "C# Script" };
	float variable1 = 50;
	//CsScript script;

	static const char* AssetNames[] = { "C# script","C++ Script", "Folder" , "C++ Component" , "Lua Script" , "GLSL Shader"};
	UiLayer::UiLayer() {
		viewRect.W = SCREEN_WIDTH;
		viewRect.H = SCREEN_HEIGHT;
	}

	void UiLayer::Initialiaze() {
		IMGUI_CHECKVERSION();
		ImGui::CreateContext();
		ImGuiIO& IO = ImGui::GetIO(); (void)IO;

		SetGuiStyle();
		IO.ConfigFlags |= ImGuiConfigFlags_DockingEnable;
		IO.ConfigFlags |= ImGuiConfigFlags_ViewportsEnable;
		IO.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;

		IO.Fonts->AddFontFromFileTTF("Resource/Fonts/Roboto-Medium.ttf", 14.0f);
		IO.Fonts->AddFontFromFileTTF("Resource/Fonts/Roboto-Medium.ttf", 11.5f);

		ImGui_ImplOpenGL3_Init("#version 330");
		ImGui_ImplGlfw_InitForOpenGL(&Core.Window(), true);

		window_flags = ImGuiWindowFlags_MenuBar | ImGuiWindowFlags_NoDocking | ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoCollapse |
			ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoBringToFrontOnFocus | ImGuiWindowFlags_NoNavFocus | ImGuiWindowFlags_NoBackground;				

		// load icons
		LoadIcons();

		// scene frame texture
		sceneFrameTexture = (ImTextureID)Core.GetSceneBufferID()->GetID();
		lastSelectedEntity = selectedEntity = ECS::INVALID_ENTITY;

		compUIs.push_back(std::move(std::make_shared<NameTagUI>()));
		compUIs.push_back(std::move(std::make_shared<TransformUI>()));
		compUIs.push_back(std::move(std::make_shared<DirectLightUI>()));
		compUIs.push_back(std::move(std::make_shared<PointLightUI>()));
		compUIs.push_back(std::move(std::make_shared<MeshUI>()));
		compUIs.push_back(std::move(std::make_shared<CsScriptCompUI>()));
		compUIs.push_back(std::move(std::make_shared<ModelCompUI>()));
		compUIs.push_back(std::move(std::make_shared<RBUI>()));
		compUIs.push_back(std::move(std::make_shared<CamUI>()));
	}

	void UiLayer::Display() {
		ImGui_ImplOpenGL3_NewFrame();
		ImGui_ImplGlfw_NewFrame();
		ImGui::NewFrame();
		ImGuizmo::BeginFrame();

		Dockspace();
		Viewport();
		Components();
		Entities();
		Resources();

		ToolBar();
		Console();
		//SceneSelector();
		//AssetBrowser();


		//ImGui::ShowDemoWindow();
		ImGui::Render();
		ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
		GLFWwindow* backup_current_context = glfwGetCurrentContext();
		ImGui::UpdatePlatformWindows();
		ImGui::RenderPlatformWindowsDefault();
		glfwMakeContextCurrent(backup_current_context);
	}

	void UiLayer::LoadIcons() {
		icons.insert({ "obj", (ImTextureID)fr::Resource.LoadTex2D("Resource/Icons/obj.png") });
		icons.insert({ "light", (ImTextureID)fr::Resource.LoadTex2D("Resource/Icons/light.png") });
		icons.insert({ "camera", (ImTextureID)fr::Resource.LoadTex2D("Resource/Icons/camera.png") });

		icons.insert({ "up", (ImTextureID)fr::Resource.LoadTex2D("Resource/Icons/up.png") });
		icons.insert({ "down", (ImTextureID)fr::Resource.LoadTex2D("Resource/Icons/down.png") });
		icons.insert({ "plus", (ImTextureID)fr::Resource.LoadTex2D("Resource/Icons/add.png") });
		icons.insert({ "minus", (ImTextureID)fr::Resource.LoadTex2D("Resource/Icons/minus.png") });

		icons.insert({ "play", (ImTextureID)fr::Resource.LoadTex2D("Resource/Icons/play.png") });
		icons.insert({ "scale", (ImTextureID)fr::Resource.LoadTex2D("Resource/Icons/scale.png") });
		icons.insert({ "Logo", (ImTextureID)fr::Resource.LoadTex2D("Resource/Icons/old/folder123.png") });
		icons.insert({ "move", (ImTextureID)fr::Resource.LoadTex2D("Resource/Icons/move.png") });
		icons.insert({ "rotate", (ImTextureID)fr::Resource.LoadTex2D("Resource/Icons/rotate.png") });
		icons.insert({ "folder", (ImTextureID)fr::Resource.LoadTex2D("Resource/Icons/folder.png") });
		icons.insert({ "save", (ImTextureID)fr::Resource.LoadTex2D("Resource/Icons/save.png") });
		icons.insert({ "build", (ImTextureID)fr::Resource.LoadTex2D("Resource/Icons/build.png") });
		icons.insert({ "mag",(ImTextureID)fr::Resource.LoadTex2D("Resource/Icons/magnes.png") });
		icons.insert({ "trash",(ImTextureID)fr::Resource.LoadTex2D("Resource/Icons/trash.png") });
		icons.insert({ "view",(ImTextureID)fr::Resource.LoadTex2D("Resource/Icons/view.png") });
	}

	void UiLayer::SetGuiStyle() {
		ImGuiStyle& style = ImGui::GetStyle();
		ImVec4* colors = style.Colors;

		/// 0 = FLAT APPEARENCE
		/// 1 = MORE "3D" LOOK
		int is3D = 0;
		colors[ImGuiCol_Text] = ImVec4(1.00f, 1.00f, 1.00f, 1.00f);
		colors[ImGuiCol_TextDisabled] = ImVec4(0.40f, 0.40f, 0.40f, 1.00f);
		colors[ImGuiCol_ChildBg] = ImVec4(0.25f, 0.25f, 0.25f, 1.00f);
		colors[ImGuiCol_WindowBg] = ImVec4(0.25f, 0.25f, 0.25f, 1.00f);
		colors[ImGuiCol_PopupBg] = ImVec4(0.25f, 0.25f, 0.25f, 1.00f);
		colors[ImGuiCol_Border] = ImVec4(0.12f, 0.12f, 0.12f, 0.71f);
		colors[ImGuiCol_BorderShadow] = ImVec4(1.00f, 1.00f, 1.00f, 0.06f);
		colors[ImGuiCol_FrameBg] = ImVec4(0.2f, 0.42f, 0.42f, 0.54f);
		colors[ImGuiCol_FrameBgHovered] = ImVec4(0.42f, 0.42f, 0.42f, 0.40f);
		colors[ImGuiCol_FrameBgActive] = ImVec4(0.56f, 0.56f, 0.56f, 0.67f);
		colors[ImGuiCol_TitleBg] = ImVec4(0.19f, 0.19f, 0.19f, 1.00f);
		colors[ImGuiCol_TitleBgActive] = ImVec4(0.22f, 0.22f, 0.22f, 1.00f);
		colors[ImGuiCol_TitleBgCollapsed] = ImVec4(0.17f, 0.17f, 0.17f, 0.90f);
		colors[ImGuiCol_MenuBarBg] = ImVec4(0.0f, 0.0f, 0.0f, 1.000f);
		colors[ImGuiCol_ScrollbarBg] = ImVec4(0.24f, 0.24f, 0.24f, 0.53f);
		colors[ImGuiCol_ScrollbarGrab] = ImVec4(0.41f, 0.41f, 0.41f, 1.00f);
		colors[ImGuiCol_ScrollbarGrabHovered] = ImVec4(0.52f, 0.52f, 0.52f, 1.00f);
		colors[ImGuiCol_ScrollbarGrabActive] = ImVec4(0.76f, 0.76f, 0.76f, 1.00f);
		colors[ImGuiCol_CheckMark] = ImVec4(0.65f, 0.65f, 0.65f, 1.00f);
		colors[ImGuiCol_SliderGrab] = ImVec4(0.52f, 0.52f, 0.52f, 1.00f);
		colors[ImGuiCol_SliderGrabActive] = ImVec4(0.64f, 0.64f, 0.64f, 1.00f);
		colors[ImGuiCol_Button] = ImVec4(0.54f, 0.54f, 0.54f, 0.35f);
		colors[ImGuiCol_ButtonHovered] = ImVec4(0.52f, 0.52f, 0.52f, 0.59f);
		colors[ImGuiCol_ButtonActive] = ImVec4(0.76f, 0.76f, 0.76f, 1.00f);
		colors[ImGuiCol_Header] = ImVec4(0.38f, 0.38f, 0.38f, 1.00f);
		colors[ImGuiCol_HeaderHovered] = ImVec4(0.47f, 0.47f, 0.47f, 1.00f);
		colors[ImGuiCol_HeaderActive] = ImVec4(0.76f, 0.76f, 0.76f, 0.77f);
		colors[ImGuiCol_Separator] = ImVec4(0.000f, 0.000f, 0.000f, 0.137f);
		colors[ImGuiCol_SeparatorHovered] = ImVec4(0.700f, 0.671f, 0.600f, 0.290f);
		colors[ImGuiCol_SeparatorActive] = ImVec4(0.702f, 0.671f, 0.600f, 0.674f);
		colors[ImGuiCol_ResizeGrip] = ImVec4(0.26f, 0.59f, 0.98f, 0.25f);
		colors[ImGuiCol_ResizeGripHovered] = ImVec4(0.26f, 0.59f, 0.98f, 0.67f);
		colors[ImGuiCol_ResizeGripActive] = ImVec4(0.26f, 0.59f, 0.98f, 0.95f);
		colors[ImGuiCol_PlotLines] = ImVec4(0.61f, 0.61f, 0.61f, 1.00f);
		colors[ImGuiCol_PlotLinesHovered] = ImVec4(1.00f, 0.43f, 0.35f, 1.00f);
		colors[ImGuiCol_PlotHistogram] = ImVec4(0.90f, 0.70f, 0.00f, 1.00f);
		colors[ImGuiCol_PlotHistogramHovered] = ImVec4(1.00f, 0.60f, 0.00f, 1.00f);
		colors[ImGuiCol_TextSelectedBg] = ImVec4(0.73f, 0.73f, 0.73f, 0.35f);
		colors[ImGuiCol_ModalWindowDimBg] = ImVec4(0.80f, 0.80f, 0.80f, 0.35f);
		colors[ImGuiCol_DragDropTarget] = ImVec4(1.00f, 1.00f, 0.00f, 0.90f);
		colors[ImGuiCol_NavHighlight] = ImVec4(0.26f, 0.59f, 0.98f, 1.00f);
		colors[ImGuiCol_NavWindowingHighlight] = ImVec4(1.00f, 1.00f, 1.00f, 0.70f);
		colors[ImGuiCol_NavWindowingDimBg] = ImVec4(0.80f, 0.80f, 0.80f, 0.20f);

		style.PopupRounding = 3;

		style.WindowPadding = ImVec2(4, 4);
		style.FramePadding = ImVec2(6, 4);
		style.ItemSpacing = ImVec2(6, 2);

		style.ScrollbarSize = 18;

		style.WindowBorderSize = 1;
		style.ChildBorderSize = 1;
		style.PopupBorderSize = 1;
		style.FrameBorderSize = is3D;

		style.WindowRounding = 3;
		style.ChildRounding = 3;
		style.FrameRounding = 3;
		style.ScrollbarRounding = 2;
		style.GrabRounding = 3;

#ifdef IMGUI_HAS_DOCK 
		style.TabBorderSize = is3D;
		style.TabRounding = 3;

		colors[ImGuiCol_DockingEmptyBg] = ImVec4(0.38f, 0.38f, 0.38f, 1.00f);
		colors[ImGuiCol_Tab] = ImVec4(0.25f, 0.25f, 0.25f, 1.00f);
		colors[ImGuiCol_TabHovered] = ImVec4(0.40f, 0.40f, 0.40f, 1.00f);
		colors[ImGuiCol_TabActive] = ImVec4(0.33f, 0.33f, 0.33f, 1.00f);
		colors[ImGuiCol_TabUnfocused] = ImVec4(0.25f, 0.25f, 0.25f, 1.00f);
		colors[ImGuiCol_TabUnfocusedActive] = ImVec4(0.33f, 0.33f, 0.33f, 1.00f);
		colors[ImGuiCol_DockingPreview] = ImVec4(0.85f, 0.85f, 0.85f, 0.28f);

		if (ImGui::GetIO().ConfigFlags & ImGuiConfigFlags_ViewportsEnable)
		{
			style.WindowRounding = 0.0f;
			style.Colors[ImGuiCol_WindowBg].w = 1.0f;
		}
#endif
	}
	void UiLayer::DarkTheme() {
		ImGuiStyle& style = ImGui::GetStyle();
		ImVec4* colors = style.Colors;

		colors[ImGuiCol_Text] = ImVec4(1.00f, 1.00f, 1.00f, 1.00f);
		colors[ImGuiCol_TextDisabled] = ImVec4(0.40f, 0.40f, 0.40f, 1.00f);
		colors[ImGuiCol_ChildBg] = ImVec4(0.25f, 0.25f, 0.25f, 1.00f);
		colors[ImGuiCol_WindowBg] = ImVec4(0.25f, 0.25f, 0.25f, 1.00f);
		colors[ImGuiCol_PopupBg] = ImVec4(0.25f, 0.25f, 0.25f, 1.00f);
		colors[ImGuiCol_Border] = ImVec4(0.12f, 0.12f, 0.12f, 0.71f);
		colors[ImGuiCol_BorderShadow] = ImVec4(1.00f, 1.00f, 1.00f, 0.06f);
		colors[ImGuiCol_FrameBg] = ImVec4(0.42f, 0.42f, 0.42f, 0.54f);
		colors[ImGuiCol_FrameBgHovered] = ImVec4(0.42f, 0.42f, 0.42f, 0.40f);
		colors[ImGuiCol_FrameBgActive] = ImVec4(0.56f, 0.56f, 0.56f, 0.67f);
		colors[ImGuiCol_TitleBg] = ImVec4(0.19f, 0.19f, 0.19f, 1.00f);
		colors[ImGuiCol_TitleBgActive] = ImVec4(0.22f, 0.22f, 0.22f, 1.00f);
		colors[ImGuiCol_TitleBgCollapsed] = ImVec4(0.17f, 0.17f, 0.17f, 0.90f);
		colors[ImGuiCol_MenuBarBg] = ImVec4(0.335f, 0.335f, 0.335f, 1.000f);
		colors[ImGuiCol_ScrollbarBg] = ImVec4(0.24f, 0.24f, 0.24f, 0.53f);
		colors[ImGuiCol_ScrollbarGrab] = ImVec4(0.41f, 0.41f, 0.41f, 1.00f);
		colors[ImGuiCol_ScrollbarGrabHovered] = ImVec4(0.52f, 0.52f, 0.52f, 1.00f);
		colors[ImGuiCol_ScrollbarGrabActive] = ImVec4(0.76f, 0.76f, 0.76f, 1.00f);
		colors[ImGuiCol_CheckMark] = ImVec4(0.65f, 0.65f, 0.65f, 1.00f);
		colors[ImGuiCol_SliderGrab] = ImVec4(0.52f, 0.52f, 0.52f, 1.00f);
		colors[ImGuiCol_SliderGrabActive] = ImVec4(0.64f, 0.64f, 0.64f, 1.00f);
		colors[ImGuiCol_Button] = ImVec4(0.54f, 0.54f, 0.54f, 0.35f);
		colors[ImGuiCol_ButtonHovered] = ImVec4(0.52f, 0.52f, 0.52f, 0.59f);
		colors[ImGuiCol_ButtonActive] = ImVec4(0.76f, 0.76f, 0.76f, 1.00f);
		colors[ImGuiCol_Header] = ImVec4(0.31f, 0.31f, 0.31f, 1.00f);
		colors[ImGuiCol_HeaderHovered] = ImVec4(0.44f, 0.44f, 0.44f, 1.00f);
		colors[ImGuiCol_HeaderActive] = ImVec4(0.74f, 0.74f, 0.74f, 0.77f);
		colors[ImGuiCol_Separator] = ImVec4(0.000f, 0.000f, 0.000f, 0.137f);
		colors[ImGuiCol_SeparatorHovered] = ImVec4(0.700f, 0.671f, 0.600f, 0.290f);
		colors[ImGuiCol_SeparatorActive] = ImVec4(0.702f, 0.671f, 0.600f, 0.674f);
		colors[ImGuiCol_ResizeGrip] = ImVec4(0.26f, 0.59f, 0.98f, 0.25f);
		colors[ImGuiCol_ResizeGripHovered] = ImVec4(0.26f, 0.59f, 0.98f, 0.67f);
		colors[ImGuiCol_ResizeGripActive] = ImVec4(0.26f, 0.59f, 0.98f, 0.95f);
		colors[ImGuiCol_PlotLines] = ImVec4(0.61f, 0.61f, 0.61f, 1.00f);
		colors[ImGuiCol_PlotLinesHovered] = ImVec4(1.00f, 0.43f, 0.35f, 1.00f);
		colors[ImGuiCol_PlotHistogram] = ImVec4(0.90f, 0.70f, 0.00f, 1.00f);
		colors[ImGuiCol_PlotHistogramHovered] = ImVec4(1.00f, 0.60f, 0.00f, 1.00f);
		colors[ImGuiCol_TextSelectedBg] = ImVec4(0.73f, 0.73f, 0.73f, 0.35f);
		colors[ImGuiCol_ModalWindowDimBg] = ImVec4(0.80f, 0.80f, 0.80f, 0.35f);
		colors[ImGuiCol_DragDropTarget] = ImVec4(1.00f, 1.00f, 0.00f, 0.90f);
		colors[ImGuiCol_NavHighlight] = ImVec4(0.26f, 0.59f, 0.98f, 1.00f);
		colors[ImGuiCol_NavWindowingHighlight] = ImVec4(1.00f, 1.00f, 1.00f, 0.70f);
		colors[ImGuiCol_NavWindowingDimBg] = ImVec4(0.80f, 0.80f, 0.80f, 0.20f);
	}

	

	void UiLayer::Dockspace() {
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

	void UiLayer::MenuBar() {
		if (ImGui::BeginMenuBar()) {
			//if(Widget::ToolButton::Show(icons.at("Logo"))){
				//console = console + "\n [DEBUG] TAM TAM TAMMMMM";
			//}
			if (ImGui::BeginMenu("File")) {
				if (ImGui::MenuItem("New Scene", "Ctrl+N")) {
					const char* file = "";
					//fr::Serializer.SaveScene(file);
					//MessageBox(0, "This Function is not aviable in BETA relase!!", "INFO", 0);
				}

				if (ImGui::MenuItem("Open Scene", "Ctrl+O")) {

				}

				if (ImGui::MenuItem("Save", "Ctrl+S")) { fr::Serializer.SaveScene("Resource/Scene/scene.fr"); }

				if (ImGui::MenuItem("Save As..")) {}
				ImGui::EndMenu();
			}
			if (ImGui::BeginMenu("Editor")) {
				if (ImGui::MenuItem("Undo", "CTRL+Z")) {}
				if (ImGui::MenuItem("Redo", "CTRL+Y", false, false)) {}  // Disabled item
				ImGui::Separator();
				if (ImGui::MenuItem("Cut", "CTRL+X")) {}
				if (ImGui::MenuItem("Copy", "CTRL+C")) {}
				if (ImGui::MenuItem("Paste", "CTRL+V")) {}
				ImGui::EndMenu();
			}
			if (ImGui::BeginMenu("Settings")) {
				if (ImGui::MenuItem("Normal Theme")) { SetGuiStyle(); }
				if (ImGui::MenuItem("Dark Theme")) { DarkTheme(); }
				if (ImGui::MenuItem("Light Theme")) {}
				ImGui::EndMenu();
			}
			if (ImGui::BeginMenu("Window")) {
				if (ImGui::MenuItem("Fractal Store", "soon")) {}
				if (ImGui::MenuItem("Inspector")) { Components(); InitCompUI(); }
				if (ImGui::MenuItem("Entities")) { Entities(); }
				if (ImGui::MenuItem("Console")) {  }
				if (ImGui::MenuItem("Resources")) {  }
				if (ImGui::MenuItem("Visual Studio Code Scripts")) { 
					system("cd Resource/Scripts");
					system("code Resource/Scripts/.");
				}
				ImGui::EndMenu();
			}
			if (ImGui::BeginMenu("Tools")) {
				if (ImGui::MenuItem("Rotate")) { gizmo.Operation = ImGuizmo::OPERATION::ROTATE; }
				if (ImGui::MenuItem("Move")) { gizmo.Operation = ImGuizmo::OPERATION::TRANSLATE; }
				if (ImGui::MenuItem("Scale")) { gizmo.Operation = ImGuizmo::OPERATION::SCALE; }
				ImGui::EndMenu();
			}
			if (ImGui::BeginMenu("Help")) {
				if (ImGui::MenuItem("View Help", "Ctrl+H")) {}
				if (ImGui::MenuItem("About Fractal Engine")) {}
				ImGui::EndMenu();
			}

			ImGui::EndMenuBar();
		}
	}

	void UiLayer::Viewport() {		
		ImGui::Begin("Scene", nullptr);
		{			
			ImGui::PushStyleColor(ImGuiCol_FrameBg, ImVec4(dark));
			ImGui::BeginChildFrame(ImGui::GetID("toolbar"), ImVec2(0,32));
			{
				if (Widget::ToolButton::Show(icons.at("move"))) { gizmo.Operation = ImGuizmo::OPERATION::TRANSLATE; console = console + "\n [DEBUG] Tool Move "; }
				ImGui::SameLine();
				ImGui::Dummy(ImVec2(2, 0));

				ImGui::SameLine();
				if (Widget::ToolButton::Show(icons.at("rotate"))) { gizmo.Operation = ImGuizmo::OPERATION::ROTATE;  console = console + "\n [DEBUG] Tool Rotate ";}
				ImGui::SameLine();

				ImGui::SameLine();
				if (Widget::ToolButton::Show(icons.at("scale"))) { gizmo.Operation = ImGuizmo::OPERATION::SCALE; console = console + "\n [DEBUG] Tool Scale ";}
				ImGui::SameLine();

				if (Widget::ToolButton::Show(icons.at("mag"))) {
					console = console + "\n [DEBUG] Tool Magnes ";
				
				}
				ImGui::SameLine();
				ImGui::Dummy(ImVec2(48, 0));

				ImGui::SameLine();
				if (ImGui::Button("Save Scene")) { 
					fr::Serializer.SaveScene("Resource/Scene/scene.fr"); 
					console = console + "\n [DEBUG] Saved Scene scene.fr!";
				}
				ImGui::SameLine();
				ImGui::Dummy(ImVec2(2, 0));

				//ImGui::SameLine();
				//if (Widget::ToolButton::Show(icons.at("build"))) {
					//Core.StopGame();
				//}

				ImGui::SameLine();
				if (Widget::ToolButton::Show(icons.at("play"))) { 					
					Core.StartGame();
				}
				ImGui::SameLine();
				ImGui::Dummy(ImVec2(2, 0));
				ImGui::SameLine();


			}
			ImGui::EndChildFrame();
			ImGui::PopStyleColor();			
			ImGui::PushStyleVar(ImGuiStyleVar_FramePadding, ImVec2(0,0));	
			ImGui::BeginChildFrame(ImGui::GetID("sceneFrame"), ImVec2(0,0), ImGuiWindowFlags_NoScrollbar);
			{	
				const ImVec2& size = ImGui::GetWindowSize();
				ImGui::Image(sceneFrameTexture, size, ImVec2(0,1), ImVec2(1,0));		
				const ImVec2& pos = ImGui::GetWindowPos();
				viewRect = { pos.x, pos.y, size.x, size.y };				
				TransformGizmo();
			}
			ImGui::PopStyleVar();			
			ImGui::EndChildFrame();
		}
		ImGui::End();
	}


	void UiLayer::Components() {
		ImGui::Begin("Inspector", nullptr);
		{
			// toolbar		
			ImGui::PushStyleColor(ImGuiCol_FrameBg, dark);
			ImGui::BeginChildFrame(ImGui::GetID("toolbar"), ImVec2(0, 32));
			{
				if (ImGui::Button("Add Component")) {
					ImGui::OpenPopup("compPopup");
				}
				ImGui::SameLine();
				if (Widget::ToolButton::Show(icons.at("trash"), 20.0f)) {}
				ImGui::SameLine();
				if (ImGui::BeginPopup("compPopup")) {
					ImGui::Text("Components");
					ImGui::Separator();

					for (size_t i = 0; i < IM_ARRAYSIZE(names); i++) {
						if (ImGui::Selectable(names[i])) {
							AddComponent(names[i]);
							console = console + "\n [ECS] Added Component " + names[i];
						}
					}
					ImGui::EndPopup();
				}
			}
			ImGui::PopStyleColor();
			ImGui::EndChildFrame();
			ImGui::Text("Components: ");
			// components			
			if (selectedEntity > ECS::INVALID_ENTITY) {
				for (auto compUi : activeCompUIs) {
					compUi->Show();
				}

			} 

		}
		ImGui::End();
	}

	void UiLayer::Console() {
		ImGui::Begin("Output", nullptr);
		{
			ImGui::PushStyleColor(ImGuiCol_FrameBg, dark);
			ImGui::BeginChildFrame(ImGui::GetID("cframe"), ImVec2(0,0));
			{
				if (ImGui::Button("Clear")) { console = ""; }
				ImGui::SameLine();
				ImGui::Text("All logs you can find here!");
				ImGui::Text(console.c_str());
			}
			ImGui::PopStyleColor();
			ImGui::EndChildFrame();
		}
		ImGui::End();
	}

	void UiLayer::Resources() {
		ImGui::Begin("Resources Folder", nullptr);
		{
			ImGui::PushStyleColor(ImGuiCol_FrameBg, dark);
			ImGui::BeginChildFrame(ImGui::GetID("rframe"), ImVec2(0, 0));
			{
				if (Widget::ToolButton::Show(icons.at("plus"), 20.0f)) {
					ImGui::OpenPopup("compPopup2");
				}

				ImGui::SameLine();
				if (ImGui::BeginPopup("compPopup2")) {
					ImGui::Text("Add Asset");
					ImGui::Separator();

					for (size_t i = 0; i < IM_ARRAYSIZE(AssetNames); i++) {
						if (ImGui::Selectable(AssetNames[i])) {
							AddAsset(AssetNames[i]);
							console = console + "\n [DEBUG] Added new Asset! " + AssetNames[i];
						}
					}
					ImGui::EndPopup();
				}
				
				if (ImGui::Button("Open in VsCode")) {
					system("code Resource/.");
				}
				//if (ImGui::Button("Compile All C# Scripts")) {
				//	system("csc Resource/Scripts/*.cs -target:library");
				//}
				OnImGui("Resource");
			}
			ImGui::PopStyleColor();
			ImGui::EndChildFrame();
		}
		ImGui::End();		
	}

	void UiLayer::CodeEditor() {
		ImGui::Begin("Scripter", nullptr);
		{
			ImGui::PushStyleColor(ImGuiCol_FrameBg, dark);
		}
	}
	void UiLayer::ToolBar() {
		ImGui::Begin("ToolBar", nullptr);
		{
				if (ImGui::Button("Play Game")) { Core.StartGame(); }
				ImGui::SameLine();
				if (ImGui::Button("Play Scene")) { Core.StartGame(); }

				if (ImGui::CollapsingHeader("View Port")) {
					if (Widget::ToolButton::Show(icons.at("move"))) { gizmo.Operation = ImGuizmo::OPERATION::TRANSLATE; }
					ImGui::SameLine();

					ImGui::SameLine();
					if (Widget::ToolButton::Show(icons.at("rotate"))) { gizmo.Operation = ImGuizmo::OPERATION::ROTATE; }
					ImGui::SameLine();

					ImGui::SameLine();
					if (Widget::ToolButton::Show(icons.at("scale"))) { gizmo.Operation = ImGuizmo::OPERATION::SCALE; }
					ImGui::SameLine();

					if (ImGui::Button("Colision")) {}
					ImGui::SameLine();

					if (ImGui::Button(" Sound  ")) {}
					ImGui::SameLine();

					if (ImGui::Button("  Add   ")) {}
				}
				if (ImGui::CollapsingHeader("Models Browser")) {
					if (ImGui::BeginPopup("compPopup2")) {
						ImGui::Text("Add Asset");
						ImGui::Separator();

						for (size_t i = 0; i < IM_ARRAYSIZE(AssetNames); i++) {
							if (ImGui::Selectable(AssetNames[i])) {
								AddAsset(AssetNames[i]);
							}
						}
						ImGui::EndPopup();
					}

					OnImGui("Resource/Models/");
				}
				if (ImGui::CollapsingHeader("Editor")) {
					
					ImGui::Text("Editor Camera Speed");
					ImGui::DragFloat("##intensity", &variable1, 1.0f, 0, 0, "%.1f");

				}
				if (ImGui::CollapsingHeader("Inputs")) {}
				if (ImGui::CollapsingHeader("Physics System")) {}
				if (ImGui::CollapsingHeader("Scripts")) {}
		}
		ImGui::End();
	}
	void UiLayer::AssetBrowser() {
		//ImGui::PushStyleColor(ImGuiCol_FrameBg, dark);
		ImGui::Begin("Models Browser", nullptr);
		//if (Widget::ToolButton::Show(icons.at("plus"), 20.0f)) {
			//ImGui::OpenPopup("compPopup2");
		//}
		if (ImGui::BeginPopup("compPopup2")) {
			ImGui::Text("Add Asset");
			ImGui::Separator();

			for (size_t i = 0; i < IM_ARRAYSIZE(AssetNames); i++) {
				if (ImGui::Selectable(AssetNames[i])) {
					AddAsset(AssetNames[i]);
					console = console + "\n [DEBUG] Added new Asset! " + AssetNames[i];
				}
			}
			ImGui::EndPopup();
		}

		OnImGui("Resource/Models/");

		ImGui::End();
	}

	void UiLayer::Entities() {

		ImGui::Begin("Entities", nullptr);
		{
			// toolbar
			ImGui::PushStyleColor(ImGuiCol_FrameBg, dark);
			ImGui::BeginChildFrame(ImGui::GetID("toolbar"), ImVec2(0, 32));
			{
				if (Widget::ToolButton::Show(icons.at("plus"), 20.0f)) {
					AddNewEntity();
					console = console + "\n [DEBUG] Added new Entity!";
				}

				ImGui::SameLine();
				if (Widget::ToolButton::Show(icons.at("minus"), 20.0f)) {
					RemoveEntity();
					console = console + "\n [DEBUG] Deleted Entity!";
				}

				ImGui::SameLine();
				if (Widget::ToolButton::Show(icons.at("up"), 20.0f)) {
					MoveEntityUp();
					console = console + "\n [DEBUG] Moved Entity UP";
				}

				ImGui::SameLine();
				if (Widget::ToolButton::Show(icons.at("down"), 20.0f)) {
					MoveEntityDown();
					console = console + "\n [DEBUG] Moved Entity Down";
				}

				ImGui::SameLine();
				if (Widget::ToolButton::Show(icons.at("view"), 20.0f)) {}
			}
			ImGui::PopStyleColor();
			ImGui::EndChildFrame();

			// entities

			ImGui::PushStyleVar(ImGuiStyleVar_FramePadding, ImVec2(8,8));			
			ImGui::PushStyleColor(ImGuiCol_FrameBg, dark);
			ImGui::BeginChildFrame(ImGui::GetID("eframe"), ImVec2(0,0));
			{
				for (const auto& entity : entities) {
					lastSelectedEntity = selectedEntity;
					selectedEntity = Widget::Selectable::Show(std::get<1>(entity).c_str(), std::get<0>(entity), selectedEntity, std::get<2>(entity));
					if (selectedEntity != lastSelectedEntity) { 
						InitCompUI(); 
						gizmo.cTransform = &ECS::Manager.GetComponent<Transform>(selectedEntity);
						gizmo.Model = gizmo.cTransform->Model();
					}
				}
			}
			ImGui::PopStyleVar();
			ImGui::PopStyleColor();
			ImGui::EndChildFrame();
		}
		ImGui::End();
	}

	// ACTIONS

	void UiLayer::MoveEntityUp() {
		auto it = std::find_if(entities.begin(), entities.end(),
			[&](const EntityField& field) { return std::get<0>(field) == selectedEntity; });

		if (it == entities.end()) { return; }

		int pos = std::distance(entities.begin(), it);
		if (pos > 0) {
			int prev = pos - 1;
			const EntityField temp = entities[prev];
			entities[prev] = *it;
			entities[pos] = temp;
		}
	}

	void UiLayer::MoveEntityDown() {
		auto it = std::find_if(entities.begin(), entities.end(),
			[&](const EntityField& field) { return std::get<0>(field) == selectedEntity; });

		if (it == entities.end()) { return; }

		int pos = std::distance(entities.begin(), it);
		if (pos < entities.size() - 1) {
			const EntityField temp = entities[pos + 1];
			entities[pos + 1] = *it;
			entities[pos] = temp;
		}
	}

	void UiLayer::AddNewEntity() {
		// Creating Entity
		ECS::Entity entity;
		selectedEntity = entity.GetID();
		auto name = "Entity" + std::to_string(selectedEntity);
		entity.AddComponent<EntityName>(name.c_str());
		entity.AddComponent<Transform>();

		//if (entity.HasComponent<CsScript>()) {
			//entity.GetComponent<CsScript>().AssemblyPath = "";
		//}
		

		// End

		AddExistingEntity(entity.GetID());
		InitCompUI();
	}

	void UiLayer::RemoveEntity() {
		if (selectedEntity > ECS::INVALID_ENTITY) {
			ECS::Manager.DestroyEntity(selectedEntity);
			auto it = std::find_if(entities.begin(), entities.end(),
				[&](const EntityField& field) { return std::get<0>(field) == selectedEntity; });

			if (it != entities.end()) {
				entities.erase(it);
			}
			selectedEntity = (entities.size() > 1) ? std::get<0>(entities.back()) : ECS::INVALID_ENTITY;
		}

		InitCompUI();
	}

	void UiLayer::AddComponent(const char* typeName) {
		if (selectedEntity > ECS::INVALID_ENTITY) {
			ECS::Manager.AddComponent(selectedEntity, typeName);
			InitCompUI();
		}
	}

	void UiLayer::RemoveComponent(const char* typeName) {
		if (selectedEntity > ECS::INVALID_ENTITY) {
			ECS::Manager.RemoveComponent(selectedEntity, typeName);
			InitCompUI();
		}
	}

	void UiLayer::AddAsset(const char* Name) {
		if (Name == "C# script") {
			std::fstream file;
			std::string Path = "Resource/Scripts/Script";
			std::string f = ".cs";
			file.open(Path + f, std::ios::out);
			std::string code;
			code = "using Fractal;\n\npublic class TestScript : FractalScript\n{\n    public void Start() { // Start Function \n \n \n    }\n    public void Update(float deltatime, ref Transform transform){ \n \n    } \n }";
			file << code << std::endl;
			file.close();
		}
		if (Name == "GLSL Shader") {
			std::fstream file;
			std::string Path = "Resource/Shaders/Shader";
			std::string f = ".glsl";
			file.open(Path + f, std::ios::out);
			std::string code;
			code = "#version 330 core\n \n void main() {\n\n }";
			file << code << std::endl;
			file.close();
		}
		if (Name == "C++ Component") {
			std::fstream file;
			std::string Path = "Resource/Components/Component";
			std::string f = ".h";
			file.open(Path + f, std::ios::out);
			std::string code;
			code = "#pragma once \n\n #include <ECS/Base/BaseComponent.h> \n \n struct Component : public ECS::BaseComponent { \n\n};";
			file << code << std::endl;
			file.close();
		}
		if (Name == "Lua Script") {

		}
		if (Name == "Folder") {
			std::fstream file;
			std::string Path = "Resource/Folder/";
			file.open(Path, std::ios::out);
			file.close();
		}
		if (Name == "C++ Script") {
			std::fstream file;
			std::string Path = "Resource/Scripts/CppScript";
			std::string f = ".h";
			file.open(Path + f, std::ios::out);
			std::string code;
			code = "#pragma once";
			file << code << std::endl;
			file.close();


			std::fstream file2;
			std::string Path2 = "Resource/Scripts/CppScript";
			std::string f2 = ".cpp";
			file.open(Path2 + f2, std::ios::out);
			std::string code2;
			code2 = "#include 'CppScript.h'";
			file << code2 << std::endl;
			file.close();
		}
	}

	void UiLayer::AddExistingEntity(const size_t entity) {
		std::string name = ECS::Manager.GetComponent<EntityName>(entity).Value;
		ImTextureID icon = icons.at("obj");
		if (ECS::Manager.HasComponent<DirectionalLight>(entity)) {
			icon = icons.at("light");
		}
		if (ECS::Manager.HasComponent<PointLight>(entity)) {
			icon = icons.at("light");
		}
		if (ECS::Manager.HasComponent<Camera>(entity)) {
			icon = icons.at("camera");
		}
		entities.push_back(std::make_tuple(entity, name, icon));
	}

	void UiLayer::TransformGizmo() {		
		if (selectedEntity > -1) {
			ImGuizmo::SetDrawlist();
			ImGuizmo::SetOrthographic(false);
			ImGuizmo::SetRect(viewRect.X, viewRect.Y, viewRect.W, viewRect.H);

			ImGuizmo::Manipulate(glm::value_ptr(gizmo.View), glm::value_ptr(gizmo.Proj),
				gizmo.Operation, gizmo.Mode, glm::value_ptr(gizmo.Model), nullptr, (gizmo.UseSnap) ? &gizmo.Snap.x : nullptr);

			if (ImGuizmo::IsUsing()) {

				gizmo.UseSnap = false;;
				if (Events.IsKeyPressed(GLFW_KEY_LEFT_CONTROL)) {
					gizmo.UseSnap = true;
					gizmo.Snap = glm::vec3(0.5f);
					if (gizmo.Operation == ImGuizmo::ROTATE) {
						gizmo.Snap = glm::vec3(45.0f);
					}
				}

				//glm::vec3 gizmoRotation(0);
				ImGuizmo::DecomposeMatrixToComponents(glm::value_ptr(gizmo.Model),
					&gizmo.cTransform->Position.x, &gizmo.cTransform->Rotation.x, &gizmo.cTransform->Scale.x);
				//glm::vec3 deltaRotation = gizmoRotation - gizmo.cTransform->Rotation;
				//gizmo.cTransform->Rotation += deltaRotation;
			}
		}
	}

	void UiLayer::InitCompUI() {
		if (selectedEntity > ECS::INVALID_ENTITY) {
			activeCompUIs.clear();
			for (auto ui : compUIs) {
				ui->Init(selectedEntity);
				if (ui->IsVisible()) {
					activeCompUIs.push_back(ui);
				}
			}
		}
	}

	void UiLayer::OnImGui(std::string directoryPath) {
		uint32_t count = 0;
		static int selection_mask = 0;
		for (const auto& entry : std::filesystem::recursive_directory_iterator(directoryPath)) { count++; }
		auto clickState = DirectoryTreeViewRecursive(directoryPath, &count, &selection_mask);
	}

	std::pair<bool, uint32_t> UiLayer::DirectoryTreeViewRecursive(const std::filesystem::path& path, uint32_t* count, int* selection_mask) {

		ImGuiTreeNodeFlags base_flags = /* ImGuiTreeNodeFlags_OpenOnArrow | ImGuiTreeNodeFlags_OpenOnDoubleClick |*/ ImGuiTreeNodeFlags_SpanAvailWidth |
			ImGuiTreeNodeFlags_SpanFullWidth;

		bool any_node_clicked = false;
		uint32_t node_clicked = 0;

		for (const auto& entry : std::filesystem::directory_iterator(path)) {
			ImGuiTreeNodeFlags node_flags = base_flags;
			const bool is_selected = (*selection_mask & *count) != 0;
			if (is_selected)
				node_flags |= ImGuiTreeNodeFlags_Selected;

			std::string name = entry.path().string();

			auto lastSlash = name.find_last_of("/\\");
			lastSlash = (lastSlash == std::string::npos) ? 0 : lastSlash + 1;
			name = name.substr(lastSlash, name.size() - lastSlash);

			bool node_open = false;
			bool entryIsFile = !std::filesystem::is_directory(entry.path());
			if (entryIsFile) {
				node_flags |= ImGuiTreeNodeFlags_Leaf | ImGuiTreeNodeFlags_NoTreePushOnOpen;
			}
			else {
				ImGui::Image(icons.at("folder"), ImVec2(15.0f, 15.0f), ImVec2(0, 1), ImVec2(1, 0));
				ImGui::SameLine();
				node_open = ImGui::TreeNodeEx((void*)(intptr_t)(*count), node_flags, name.c_str());
			}

			if (ImGui::IsItemClicked()) {
				node_clicked = *count;
				any_node_clicked = true;
			}

			(*count)--;

			if (!entryIsFile) {
				if (node_open) {
					auto clickState = DirectoryTreeViewRecursive(entry.path(), count, selection_mask);
					if (!any_node_clicked) {
						any_node_clicked = clickState.first;
						node_clicked = clickState.second;
					}

					ImGui::TreePop();
				}
				else {
					for (const auto& e : std::filesystem::recursive_directory_iterator(entry.path()))
						(*count)--;
				}
			}
		}

		return { any_node_clicked, node_clicked };
	}
}