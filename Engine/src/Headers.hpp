#pragma once

#include "Core/Resource/Resource.h"

#include "Core/ECS/ECS.h"

#include "Core/Engine.h"

#include "Core/Timer/Timer.h"

// ECS stuff
#include "Core/ECS/Base/BaseComponent.h"
#include "Core/ECS/Base/BaseSystem.h"
#include "Core/ECS/Base/EntityManager.h"
#include "Core/ECS/Components/CsScript.h"
#include "Core/ECS/Components/EntityName.h"

#include "Editor/UiLayer.h"

// XML stuff

#include "Serializer/XMLSerializer.h"
#include "Serializer/ModelsAndTextures.h"

// Events stuff

#include "Events/AppEvents.h"
#include "Events/Dispatcher.h"
#include "Events/Event.h"
#include "Events/EventSystem.h"
#include "Events/GLFWImp.h"
#include "Events/KeyEvents.h"
#include "Events/MouseEvents.h"
#include "Events/WindowEvents.h"
#include "Editor/UiLayer.h"
#include "Core/Inputs/KeyCodes.h"

// GL stuff

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
#include "Math/Math.h"