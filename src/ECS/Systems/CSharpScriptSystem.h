#pragma once

#include "ECS/Base/BaseSystem.h"
#include "ECS/Base/EntityManager.h"

#include "Timer/Timer.h"
#include "ECS/Components/CsScript.h"

#include "ECS/Components/EntityName.h"

using namespace fr;

class CSharpScriptSystem : public ECS::BaseSystem {

public:
	~CSharpScriptSystem() = default;

	CSharpScriptSystem() : domain(nullptr) {
		AddComponentSignature<CsScript>();				
		domain = mono_jit_init("MainDomain");
	}

	void Start() override {		
		for (auto entity : entities) {
			auto& script = ECS::Manager.GetComponent<CsScript>(entity);
			script.OpenAssembly(domain);
			script.InvokeStart();
		}
	}

	void Stop() override {
		for (auto entity : entities) {
			ECS::Manager.GetComponent<CsScript>(entity).CloseAssembly();
		}
	}

	void Update() {
		float deltatime = Timer.DeltaTime();	
		void* args[3];
		args[0] = &deltatime;

		for (auto entity : entities) {
			args[1] = &ECS::Manager.GetComponent<Transform>(entity);
			args[2] = &ECS::Manager.GetComponent<EntityName>(entity);
			ECS::Manager.GetComponent<CsScript>(entity).InvokeUpdate(args);
		}
	}

private:
	MonoDomain* domain;
};