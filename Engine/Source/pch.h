#pragma once

#ifndef FR_PCH_H
#define FR_PCH_H

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

#if defined(_WIN32)
#define FR_WINDOWS
#elif defined(__linux__)
#define FR_LINUX
#elif defined(__APPLE__)
#define FR_APPLE
#elif defined(__ANDROID__)
#define FR_ANDROID
#else
#error Not Supported Platform!
#endif

#define VERSION "BETA 2.0"
#define EDITOR_VERSION "10.07.2021"
#define WINDOW_NAME "Game"

#define WINDOW_WIDTH 1280
#define WINDOW_HEIGH 720

#define BIND_FUNC(fn) std::bind(&fn, this, _1)
#define STRING(x) #x 

#define FR_NULL 0
#define FR_TRUE true
#define FR_FALSE false
#define FR_ERR -1
#define TERMS 7

#define BIT(x) 1<<x

#if defined(FR_WINDOWS)
	#include <windows.h>
#elif defined(FR_LINUX)
	#include <bits/stdc++.h>
#endif

#if defined(FR_LUA)
extern "C" {
#include "Vendor/Lua535/include/lua.h"
#include "Vendor/Lua535/include/lualib.h"
#include "Vendor/Lua535/include/lauxlib.h"
};

#pragma comment(lib, "Engine/Source/Vendor/Lua535/liblua53.a")
#endif

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#define GLM_ENABLE_EXPERIMENTAL
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtx/quaternion.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include "Math/Math.h"

using namespace std::placeholders;

#include "Core/Errors.h"
#include "Events/EventSystem.h"

namespace fr {
	using FRuint = uint32_t;
	using FRuchar = unsigned char;
	using FRboolean = bool;
	using FRchar = char;
	using FRint = int;
	using FRfloat = float;
	using FRlong = long;
	using FRvoid = void;
	typedef void(*func)();

	struct CommandLineArgs { int argc; char** args; };
}

// other includes :

#include "Core/String.h"
#include "Core/Resource/Resource.h"
#include "Core/Engine.h"
#include "Core/Timer/Timer.h"

#include "Scene/Types.h"
#include "Scene/BaseComponent.h"
#include "Scene/BaseSystem.h"
#include "Scene/CompList.h"
#include "Scene/ComponentFactory.h"
#include "Scene/Entity.h"
#include "Scene/EntityManager.h"

#include "Core/Components.h"
#include "Editor/UiLayer.h"

#include "Scene/SceneSerializer.h"

#include "Events/AppEvents.h"
#include "Events/Dispatcher.h"
#include "Events/Event.h"
#include "Events/GLFWImp.h"
#include "Events/KeyEvents.h"
#include "Events/MouseEvents.h"
#include "Events/WindowEvents.h"
#include "Editor/UiLayer.h"
#include "Events/KeyCodes.h"

#include "Renderer/ColorBuffer.h"
#include "Renderer/DepthBuffer.h"
#include "Renderer/GLMesh.h"
#include "Renderer/GLQuad.h"
#include "Renderer/Material.h"
#include "Renderer/Model.h"
#include "Renderer/SamplerBuffer.h"
#include "Renderer/Shader.h"
#include "Renderer/Vertex.h"
#include "Renderer/VertexArray.h"
#include "Renderer/Grid.h"
#include "Core/Log.h"

#endif