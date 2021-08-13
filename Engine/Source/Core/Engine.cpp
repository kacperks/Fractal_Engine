#include "pch.h"
#include "Engine.h"
#include "Editor/UiLayer.h"
#include "Scene/Entity.h"

#include "Events/GLFWImp.h"

#include "Core/Systems.h"
#include "Core/Components.h"
#include "Scene/XMLSerializer.h"
#include "Window.h"

namespace fr {

	Engine::~Engine() {
		glfwTerminate();
	}

	Engine::Engine() : isRunning(true), isGameRunnig(false), viewSize(0), window(nullptr), outputBuffer(nullptr) {
		#if defined(FR_BULID)
			std::string WinName = WINDOW_NAME;
		#else
			std::string WinName = "Fractal Engine " VERSION;
		#endif
		
		FRWindow* FRWin = new FRWindow(WinName.c_str());

		shadowBuffer = FRWin->GetDepthBuffer();
		outputBuffer = FRWin->outputBuffer;
		window = FRWin->GetWindow();
	}

	FRuint Engine::Initialize() {
		UI.AddToConsole(" [Core] Loading Fractal Enigne...");

		// register component list
		ECS::Manager.RegisterCompList<Camera>();
		ECS::Manager.RegisterCompList<Transform>();
		ECS::Manager.RegisterCompList<RigidBody>();
		ECS::Manager.RegisterCompList<SpotLight>();
		ECS::Manager.RegisterCompList<EntityName>();
		ECS::Manager.RegisterCompList<PointLight>();
		ECS::Manager.RegisterCompList<MeshRenderer>();
		ECS::Manager.RegisterCompList<ModelRenderer>();
		ECS::Manager.RegisterCompList<SpriteRenderer>();
		ECS::Manager.RegisterCompList<DirectionalLight>();

		// register component factory
		ECS::Registrar<RigidBody>("RigidBody");
		ECS::Registrar<SpotLight>("Spot Light");
		ECS::Registrar<PointLight>("Point Light");
		ECS::Registrar<MeshRenderer>("MeshRenderer");
		ECS::Registrar<ModelRenderer>("ModelRenderer");
		ECS::Registrar<SpriteRenderer>("SpriteRenderer");
		ECS::Registrar<DirectionalLight>("Directional Light");
		ECS::Registrar<Camera>("Camera");

		// register systems
		ECS::Manager.AddSystem<SpotLightSystem>();
		ECS::Manager.AddSystem<PointLightSystem>();
		ECS::Manager.AddSystem<DirectionalLightSystem>();
		ECS::Manager.AddSystem<SkyBoxRendererSystem>();

		ECS::Manager.AddSystem<MeshRendererSystem>();
		ECS::Manager.AddSystem<ModelRendererSystem>();
		ECS::Manager.AddSystem<SpriteRendererSystem>();

		// editor system will be removed at runtime
		ECS::Manager.AddEditorSystem<EditorCameraSystem>();
		ECS::Manager.AddEditorSystem<GridRendererSystem>();

		// runtime systems will be added at runtime
		ECS::Manager.AddRuntimeSystem<CameraSystem>();
		ECS::Manager.AddRuntimeSystem<PhysicsSystem>();

		#ifdef FRACTAL_CSHARP
			ECS::Manager.RegisterCompList<CsScript>();
			ECS::Registrar<CsScript>("C# Script");
			ECS::Manager.AddRuntimeSystem<CsharpScriptSystem>();
		#endif

		ECS::Manager.ActivateEditorSystems();
		ECS::Manager.Start();

		#if defined(FR_BULID)
			// Initialize Game Core	
		#endif

		fr::UI.Initialiaze();

		glfwSetKeyCallback(window, GlfwImpl::KeyboardCallback);
		glfwSetScrollCallback(window, GlfwImpl::MouseScrollCallback);
		glfwSetCursorPosCallback(window, GlfwImpl::MouseMotionCallback);
		glfwSetWindowCloseCallback(window, GlfwImpl::WindowCloseCallback);
		glfwSetMouseButtonCallback(window, GlfwImpl::MouseButtonCallback);
		glfwSetFramebufferSizeCallback(window, GlfwImpl::WindowResizedCallback);

		Dispatcher.AddListener<WindowCloseEvent>(std::bind(&Engine::OnQuit, this, _1));
		Dispatcher.AddListener<ViewportResizedEvent>(std::bind(&Engine::OnViewportResized, this, _1));

		UI.AddToConsole(" [Core] Engine loaded successfully!");

		return FR_NULL;
	}

	void Engine::Update() {
		ECS::Manager.Update();

		if (!isGameRunnig) {
			SetViewport(UI.ViewSize());
			outputBuffer->Clear();
			ECS::Manager.Render();
		}
		else {
			if (Events.IsKeyPressed(FR_KEY_ESCAPE)) {
				#ifndef FR_BULID
					StopGame();
				#endif
			}
			glfwGetWindowSize(window, &viewSize.x, &viewSize.y);
			GLCALL(glViewport(0, 0, viewSize.x, viewSize.y));
		}
	}

	void Engine::Render() {
		GLCALL(glBindFramebuffer(GL_FRAMEBUFFER, 0));
		GLCALL(glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT));

		if (!isGameRunnig) {
			fr::UI.Display();
		}
		else {
			ECS::Manager.Render();
		}

		#if defined(FR_BULID)
				Core.StartGame();
		#endif

		glfwSwapBuffers(window);
	}

	void Engine::StartGame() {
		ECS::Manager.DeactivateEditorSystems();
		ECS::Manager.ActivateRuntimeSystems();
		isGameRunnig = true;
	}

	void Engine::StopGame() {
		isGameRunnig = false;
		ECS::Manager.DeactivateRuntimeSystems();
		ECS::Manager.ActivateEditorSystems();
	}

	func Engine::SetCurrentScene(const char* NewScene) {
		Serializer.LoadScene(NewScene); 
		CurrentScene = NewScene;
		return FR_NULL;
	}
}