#pragma once

#ifndef FRACTAL
#define FRACTAL

// BASIC
#include <set>
#include <map>
#include <queue>
#include <vector>
#include <string>
#include <memory>
#include <cassert>
#include <sstream>
#include <fstream>
#include <iostream>
#include <algorithm>
#include <functional>
#include <stdio.h>

// ASSIMP

#include <ASSIMP/postprocess.h>
#include <ASSIMP/Importer.hpp>
#include <ASSIMP/scene.h>
#include <ASSIMP/camera.h>

// HEADERS

#include "Gui/Gui.h"
#include "GLObjects/GLthings.hpp"
#include "Errors/ErrorLog.h"
#include "Inputs/Inputs.h"
#include "Resource/Resource.h"
#include "Gui/Gui.h"
#include "ECS/ECS.h"
#include "vendor/imgui/imgui.h"
#include "Engine/Engine.h"
#include "Timer/Timer.h"
#include "Events/Events.h"
#include "ECS/Base/BaseComponent.h"
#include "ECS/Base/BaseSystem.h"
#include "ECS/Base/CompList.h"
#include "ECS/Base/Entity.h"
#include "ECS/Base/EntityManager.h"
#include "ECS/Base/Types.h"
#include "Serializer/XMLSerializer.h"
#include "Editor/UiLayer.h"
#include "Events/EventsCore.hpp"
#include "Editor/Ecore.hpp"
#include "Managers/Managers.hpp"

// SFML

#include <SFML/Graphics.hpp>

// OPENGL

#include <GL/glew.h>

// GLFW
#include <GLFW/glfw3.h>

// GLM
#include <glm/glm.hpp>
#include <glm/vec3.hpp> 
#include <glm/vec4.hpp> 
#include <glm/mat4x4.hpp> 
#include <glm/ext/matrix_transform.hpp> 
#include <glm/ext/matrix_clip_space.hpp>
#include <glm/ext/scalar_constants.hpp>


// VENDOR_

#include "vendor/IMGUI/imgui.h"
#include "vendor/STB/stb_image.h"

#ifdef FR_WINDOW
	// window platform related stuff
#endif

#ifdef FR_LINUX
	// linux platform related stuff
#endif

#ifdef FR_MAC
	// mac platform related stuff
#endif
#endif
