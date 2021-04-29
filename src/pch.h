#pragma once

// BASIC
#include <set>
#include <map>
#include <array>
#include <tuple>
#include <queue>
#include <vector>
#include <string>
#include <bitset>
#include <stdio.h>
#include <memory>
#include <cassert>
#include <sstream>
#include <fstream>
#include <iostream>
#include <typeinfo>
#include <algorithm>
#include <functional>
#include <filesystem>
#include <unordered_map>

using namespace std::placeholders;

// OPENGL
#include <GL/glew.h>

// GLFW
#include <GLFW/glfw3.h>

// GLM
#define GLM_ENABLE_EXPERIMENTAL
#include <GLM/glm.hpp>
#include <GLM/gtc/type_ptr.hpp>
#include <GLM/gtx/quaternion.hpp>
#include <GLM/gtc/matrix_transform.hpp>

// Custom
#include "Errors/Errors.h"
#include "Events/EventSystem.h"
#include "Core.h"
#include "fractal.hpp"

// mono

#ifdef FRACTAL_CSHARP
	#include <mono/jit/jit.h>
	#include <mono/metadata/assembly.h>
	#include <mono/metadata/debug-helpers.h>
#endif

// Platform
#ifdef FR_WINDOW
	
#endif

#ifdef FR_LINUX
	// linux platform related stuff
#endif

#ifdef FR_MAC
	// mac platform related stuff
#endif

#define VAR_NAME(var) (#var)
