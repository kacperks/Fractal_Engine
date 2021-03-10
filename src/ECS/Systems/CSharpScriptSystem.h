#pragma once

#include "ECS/Base/BaseSystem.h"
#include "ECS/Base/EntityManager.h"

#include "Timer/Timer.h"
#include "ECS/Components/CsScript.h"

using namespace Orbit3D;

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
		void* args[2];
		args[0] = &deltatime;

		for (auto entity : entities) {
			args[1] = &ECS::Manager.GetComponent<Transform>(entity);
			ECS::Manager.GetComponent<CsScript>(entity).InvokeUpdate(args);
		}
	}

private:
	MonoDomain* domain;
};