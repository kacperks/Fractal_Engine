#include "pch.h"
#include "Engine.h"
#include "Editor/UiLayer.h"
#include "ECS/Base/Entity.h"

#include "Events/GLFWImp.h"

#include "ECS/Systems.h"
#include "ECS/Components.h"
#include "Serializer/XMLSerializer.h"

namespace fr {

	Engine::~Engine() {
		glfwTerminate();
	}

	Engine::Engine(): isRuning(true), isGameRunnig(false), viewSize(0), window(nullptr), outputBuffer(nullptr) {
		glfwInit();
		glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
		glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 1);
		glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);

		auto vMode = glfwGetVideoMode(glfwGetPrimaryMonitor());

		glfwWindowHint(GLFW_SAMPLES, 4);
		glfwWindowHint(GLFW_MAXIMIZED, GL_TRUE);		
		glfwWindowHint(GLFW_RED_BITS, vMode->redBits);
		glfwWindowHint(GLFW_BLUE_BITS, vMode->blueBits);
		glfwWindowHint(GLFW_GREEN_BITS, vMode->greenBits);
		glfwWindowHint(GLFW_REFRESH_RATE, vMode->refreshRate);

		std::string WinName = "Fractal Engine " VERSION;

		window = glfwCreateWindow(WINDOW_WIDTH, WINDOW_HEIGH, WinName.c_str(), nullptr, nullptr);
		assert(window && "ERROR::GFLW::FAILED TO CREATE WINDOW!");
		glfwMakeContextCurrent(window);

		assert(glewInit() == GLEW_OK && "ERROR::GLEW INIT FAILED!");
		glewExperimental = GL_TRUE;			

		GLCALL(glEnable(GL_STENCIL_TEST));
		GLCALL(glEnable(GL_DEPTH_TEST));
		GLCALL(glEnable(GL_MULTISAMPLE))		

		shadowBuffer = new DepthBuffer(SHADOW_WIDTH, SHADOW_HEIGHT);
		outputBuffer = new SamplerBuffer(WINDOW_WIDTH, WINDOW_HEIGH);
		GLCALL(glViewport(0, 0, WINDOW_WIDTH, WINDOW_HEIGH));
		viewSize = glm::ivec2(WINDOW_WIDTH, WINDOW_HEIGH);
	}

	void Engine::Initialize(const char* scene) {

		// register component list
		ECS::Manager.RegisterCompList<Camera>();
#ifdef FRACTAL_CSHARP
		ECS::Manager.RegisterCompList<CsScript>();
#endif
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
		ECS::Registrar<Camera>("Camera");
#ifdef FRACTAL_CSHARP
		ECS::Registrar<CsScript>("C# Script");
#endif
		ECS::Registrar<RigidBody>("RigidBody");
		ECS::Registrar<SpotLight>("Spot Light");
		ECS::Registrar<PointLight>("Point Light");
		ECS::Registrar<MeshRenderer>("MeshRenderer");
		ECS::Registrar<ModelRenderer>("ModelRenderer");
		ECS::Registrar<SpriteRenderer>("SpriteRenderer");
		ECS::Registrar<DirectionalLight>("Directional Light");

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
		ECS::Manager.AddRuntimeSystem<CSharpScriptSystem>();
		#endif

		ECS::Manager.ActivateEditorSystems();
		ECS::Manager.Start();
		fr::UI.Initialiaze();
		Serializer.LoadScene(scene);

		glfwSetKeyCallback(window, GlfwImpl::KeyboardCallback);
		glfwSetScrollCallback(window, GlfwImpl::MouseScrollCallback);
		glfwSetCursorPosCallback(window, GlfwImpl::MouseMotionCallback);
		glfwSetWindowCloseCallback(window, GlfwImpl::WindowCloseCallback);
		glfwSetMouseButtonCallback(window, GlfwImpl::MouseButtonCallback);
		glfwSetFramebufferSizeCallback(window, GlfwImpl::WindowResizedCallback);

		Dispatcher.AddListener<WindowCloseEvent>(std::bind(&Engine::OnQuit, this, _1));
		Dispatcher.AddListener<ViewportResizedEvent>(std::bind(&Engine::OnViewportResized, this, _1));
#ifdef FR_BULID
		StartGame();
#endif
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
}