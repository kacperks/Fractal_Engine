#pragma once

#include "ECS/Base/BaseComponent.h"
#include "pch.h"

#include "ECS/Base/BaseSystem.h"
#include "ECS/Base/EntityManager.h"

#include "Timer/Timer.h"
#include "ECS/Components/CsScript.h"

#include "ECS/Components/EntityName.h"
#include "Editor/UiLayer.h"

// not finished yet!

struct LuaScript : public ECS::BaseComponent {
	public:
		std::string FileName = "Resource/Scripts/test.lua";
};