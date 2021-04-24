#pragma once

// HEADERS

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
#include "Editor/UiLayer.h"
// GL Headers

#include "Objects/ColorBuffer.h"
#include "Objects/DepthBuffer.h"
#include "Objects/GLMesh.h"
#include "Objects/GLQuad.h"
#include "Objects/Material.h"
#include "Objects/Model.h"
#include "Objects/SamplerBuffer.h"
#include "Objects/Shader.h"
#include "Objects/Vertex.h"
#include "Objects/VertexArray.h"