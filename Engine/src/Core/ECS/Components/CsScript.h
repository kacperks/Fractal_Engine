#pragma once

#ifdef FRACTAL_CSHARP

#include <mono/jit/jit.h>
#include <mono/metadata/assembly.h>
#include <mono/metadata/debug-helpers.h>

#include "Core/ECS/Base/BaseComponent.h"

struct CsScript : public ECS::BaseComponent {

	CsScript() {
		Assembly = mono_assembly_open(AssemblyPath.c_str(), nullptr);
	}

	~CsScript() = default;

	void OpenAssembly(MonoDomain* domain) {				
		MonoAssembly* Assembly = mono_domain_assembly_open(domain, AssemblyPath.c_str());
		MonoImage* image = mono_assembly_get_image(Assembly);
		MonoClass* sClass = mono_class_from_name(image, "", ClassName.c_str());

		Start = mono_class_get_method_from_name(sClass, "Start", 0);
		Update = mono_class_get_method_from_name(sClass, "Update", 2);

		Object = mono_object_new(domain, sClass);
		mono_runtime_object_init(Object);		
	}

	void CloseAssembly() {	
		//mono_free(Assembly);
		//mono_assembly_close(Assembly);
	}

	void InvokeStart() {
		if (Start) mono_runtime_invoke(Start, Object, nullptr, nullptr);
	}

	void InvokeUpdate(void** args) {
		if (Update) mono_runtime_invoke(Update, Object, args, nullptr);
	}

	MonoMethod* Start = nullptr;
	MonoMethod* Update = nullptr;
	MonoObject* Object = nullptr;
	MonoAssembly* Assembly = nullptr;

	public:
		std::string ClassName = "TestScript";
		std::string AssemblyPath;
};

#endif