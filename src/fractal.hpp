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

// LUA

extern "C"
{
    #include "vendor/LUA/include/lua.h"
    #include "vendor/LUA/include/lauxlib.h"
    #include "vendor/LUA/include/lualib.h"
}


// ASSIMP

#include <ASSIMP/postprocess.h>
#include <ASSIMP/Importer.hpp>
#include <ASSIMP/scene.h>
#include <ASSIMP/camera.h>

// HEADERS

    #include "Errors/ErrorLog.h"

    #include "Inputs/Inputs.h"

    #include "Resource/Resource.h"

    #include "ECS/ECS.h"

    #include "Engine/Engine.h"

    #include "Timer/Timer.h"

    // ECS Headers
    #include "ECS/Base/BaseComponent.h"
    #include "ECS/Base/BaseSystem.h"
    #include "ECS/Base/EntityManager.h"
    #include "ECS/Components/CsScript.h"
    #include "ECS/Components/EntityName.h"

    #include "Editor/UiLayer.h"

    // XML Heders

    #include "Serializer/XMLSerializer.h"

    // Events Headers

    #include "Events/AppEvents.h"
    #include "Events/Dispatcher.h"
    #include "Events/Event.h"
    #include "Events/EventSystem.h"
    #include "Events/GLFWImp.h"
    #include "Events/KeyEvents.h"
    #include "Events/MouseEvents.h"
    #include "Events/WindowEvents.h"
    #include "Editor/Ecore.hpp"
    // GL Headers

    #include "GLObjects/ColorBuffer.h"
    #include "GLObjects/DepthBuffer.h"
    #include "GLObjects/GLMesh.h"
    #include "GLObjects/GLQuad.h"
    #include "GLObjects/Material.h"
    #include "GLObjects/Model.h"
    #include "GLObjects/SamplerBuffer.h"
    #include "GLObjects/Shader.h"
    #include "GLObjects/Vertex.h"
    #include "GLObjects/VertexArray.h"

// Core

#include "core.hpp"

// MONO

#include <mono/jit/jit.h>
#include <mono/metadata/assembly.h>
#include <mono/metadata/debug-helpers.h>

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

#include "vendor/STB/stb_image.h"

#include "vendor/imgui/imgui.h"
#include "vendor/imgui/imgui_impl_glfw.h"
#include "vendor/imgui/imgui_impl_opengl3.h"

#include "vendor/GUIZMO/ImGuizmo.h"

#endif