#include "Engine.h"

#include "../Gui/Gui.h"
#include "../Errors/ErrorLog.h"
#include "../Resource/Resource.h"

#include "../ECS/Systems/Systems.h"
#include "../ECS/Components/Common.h"

Engine::Engine(): deltaTime(0.0f), lastFrame(0.0f), window(nullptr), OnRun(true),
	screenWidth(SCREEN_WIDTH), screenHeight(SCREEN_HEIGHT), mode(OperationMode::EDIT_MODE) {

	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 1);
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);

	const GLFWvidmode* videoMode = glfwGetVideoMode(glfwGetPrimaryMonitor());
	glfwWindowHint(GLFW_RED_BITS, videoMode->redBits);
	glfwWindowHint(GLFW_GREEN_BITS, videoMode->greenBits);
	glfwWindowHint(GLFW_BLUE_BITS, videoMode->blueBits);
	glfwWindowHint(GLFW_REFRESH_RATE, videoMode->refreshRate);

	window = glfwCreateWindow(videoMode->width, videoMode->height, "FuseOrbit3D", nullptr, nullptr);
	assert(window && "ERROR::GFLW::FAILED TO CREATE WINDOW!");
	glfwMakeContextCurrent(window);
	glfwSwapInterval(1);

	assert(glewInit() == GLEW_OK && "ERROR::GLEW::INIT FAILED!");
	glewExperimental = GL_TRUE;
}

Engine::~Engine(){
	glfwTerminate();
}

void Engine::Initialize() {
	// init resources
	RESOURCE.Initialize();
	// initialise entities
	InitializeEntities();
	// initialize gui layer
	GUI.Initialize();
}

void Engine::Update() {	
	UpdateDeltaTime();
	glfwPollEvents();
	screenBuffer.Clear();

	Manager.Update();
	if (mode == OperationMode::EDIT_MODE) { GUI.Display(); }

	glfwSwapBuffers(window);	
}

void Engine::InitializeEntities() {

	Manager.RegisterSystem<CameraSystem>();
	Manager.RegisterSystem<KeyMotionSystem>();
	Manager.RegisterSystem<LightSystem>();
	Manager.RegisterSystem<PhysicsSystem>();
	Manager.RegisterSystem<RendererSystem>();

	// init entities
	ECS::Entity cube1(Manager.AddEntity());
	cube1.AddComponent<Name>();
	cube1.AddComponent<Transform3D>(glm::vec3(-0.5f, -2.6f, -10.0f));
	cube1.AddComponent<Material>(RESOURCE.GetTex2D("container0"));

	// init entities
	ECS::Entity cube2(Manager.AddEntity());
	cube2.AddComponent<Name>();
	cube2.AddComponent<Transform3D>(glm::vec3(0.0f, -3.1f, -10.0f), glm::vec3(2.0f));
	cube2.AddComponent<Material>(RESOURCE.GetTex2D("container1"));

	ECS::Entity cube3(Manager.AddEntity());
	cube3.AddComponent<Name>();
	cube3.AddComponent<Transform3D>(glm::vec3(0.0f, -8.0f, -10.0f), glm::vec3(10.0f, 0.1f, 10.0f));
	cube3.AddComponent<Material>();	

	ECS::Entity camera(Manager.AddEntity());
	camera.AddComponent<Name>("MainCamera");
	camera.AddComponent<Transform3D>(glm::vec3(0.0f, 0.0f, 3.0f));
	camera.AddComponent<Camera>();

	// init scene light
	ECS::Entity light(Manager.AddEntity());
	light.AddComponent<Name>("Global Light");
	light.AddComponent<Transform3D>(glm::vec3(0.0f, 2.0f, 0.5f));
	light.AddComponent<Light>(1);
	light.AddComponent<Material>();

	GUI.AddExistingEntity(camera.GetHandle());
	GUI.AddExistingEntity(light.GetHandle());
}

void Engine::UpdateDeltaTime() {
	deltaTime = glfwGetTime() - lastFrame;
	lastFrame = glfwGetTime();
}

