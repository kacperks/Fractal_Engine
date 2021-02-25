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

// HEADERS

//Headers

#include "vendor/imgui/imgui.h"
#include "Engine/Engine.h"
#include "ECS/Base/BaseComponent.h"
#include "ECS/Base/BaseSystem.h"
#include "ECS/Base/CompList.h"
#include "ECS/Base/Entity.h"
#include "ECS/Base/EntityManager.h"
#include "ECS/Base/Types.h"

// OPENGL
#include <GLEW/glew.h>

// GLFW
#include <GLFW/glfw3.h>

// GLM
#include <GLM/glm.hpp>
#include <GLM/gtc/type_ptr.hpp>
#include <GLM/gtc/matrix_transform.hpp>

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