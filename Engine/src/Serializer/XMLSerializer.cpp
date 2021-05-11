#include "pch.h"
#include "XMLSerializer.h"

#include "Editor/UiLayer.h"
#include "ECS/Base/EntityManager.h"

namespace fr {

	// SCENE
	void XMLSerializer::LoadScene(const char* filename) {
		UiLayer::AddToConsole(" [XMLSerializer] Loaded scene.fr!");
		tinyxml2::XMLDocument document;
		document.LoadFile(filename);
		if (document.Error()) { 
			document.PrintError(); 
			return;
		}
		XMLElement* root = document.RootElement();

		// PARSE ENTITIES FROM XML
		for (XMLElement* e = root->FirstChildElement(); e != nullptr; e = e->NextSiblingElement()) {
			const ECS::EntityID entityid = ECS::Manager.AddNewEntity();			
			LoadEntity(e, entityid);
			std::string ID = "ID: " + entityid;
			fr::UI.AddExistingEntity(entityid);
		}
	}
	void XMLSerializer::SaveScene(const char* filename) {
		UiLayer::AddToConsole(" [XMLSerializer] Saved scene.fr!");
		FILE* pFile;
		fopen_s(&pFile, filename, "w");
		tinyxml2::XMLPrinter printer(pFile);

		printer.PushHeader(true, true);
		printer.OpenElement("Scene");
		for (const ECS::EntityID entityid : ECS::Manager.ActiveEntities()) {
			SaveEntity(printer, entityid);
		}
		printer.CloseElement();

		tinyxml2::XMLDocument document;
		document.Print(&printer);
		if (pFile != nullptr) { fclose(pFile); }
	}

	// ENTITY
	void XMLSerializer::LoadEntity(XMLElement* xEntity, const ECS::EntityID entityid) {
		for (XMLElement* e = xEntity->FirstChildElement(); e != nullptr; e = e->NextSiblingElement()) {
			if (e->Value() == std::string("EntityName")) {
				LoadEntityName(e, entityid);
				continue;
			}

			if (e->Value() == std::string("Transform")) {
				LoadTransform(e, entityid);
				continue;
			}

			if (e->Value() == std::string("Camera")) {
				LoadCamera(e, entityid);
				continue;
			}

			if (e->Value() == std::string("MeshRenderer")) {
				LoadMeshRenderer(e, entityid);
				continue;
			}

			if (e->Value() == std::string("ModelRenderer")) {
				LoadModelRenderer(e, entityid);
				continue;
			}

			if (e->Value() == std::string("SpotLight")) {
				LoadSpotLight(e, entityid);
				continue;
			}

			if (e->Value() == std::string("PointLight")) {
				LoadPointLight(e, entityid);
				continue;
			}

			if (e->Value() == std::string("DirectionalLight")) {
				LoadDirectionalLight(e, entityid);
				continue;
			}

			if (e->Value() == std::string("RigidBody")) {
				LoadRigidBody(e, entityid);
				continue;
			}

			if (e->Value() == std::string("SpriteRenderer")) {
				LoadSpriteRenderer(e, entityid);
				continue;
			}
			if (e->Value() == std::string("CsScript")) {
				LoadCsScript(e, entityid);
				continue;
			}
		}
	}
	void XMLSerializer::SaveEntity(XMLPrinter& printer, const ECS::EntityID entityid) {
		printer.OpenElement("Entity");
		SaveEntityName(printer, entityid);
		SaveTransform(printer, entityid);
		SaveCamera(printer, entityid);
		SaveMeshRenderer(printer, entityid);
		SaveSpriteRenderer(printer, entityid);
		SaveModelRenderer(printer, entityid);
		SaveSpotLight(printer, entityid);
		SavePointLight(printer, entityid);
		SaveDirectionalLight(printer, entityid);
		SaveRigidBody(printer, entityid);
		SaveCsScript(printer, entityid);
		printer.CloseElement();
	}

	// TRANSFORM
	void XMLSerializer::LoadTransform(XMLElement* xTransform, const ECS::EntityID entityid) {
		Transform transform;		
		transform.Position.x = xTransform->FloatAttribute("x");
		transform.Position.y = xTransform->FloatAttribute("y");
		transform.Position.z = xTransform->FloatAttribute("z");

		transform.Rotation.x = xTransform->FloatAttribute("rx");
		transform.Rotation.y = xTransform->FloatAttribute("ry");
		transform.Rotation.z = xTransform->FloatAttribute("rz");

		transform.Scale.x = xTransform->FloatAttribute("sx", 1.0f);
		transform.Scale.y = xTransform->FloatAttribute("sy", 1.0f);
		transform.Scale.z = xTransform->FloatAttribute("sz", 1.0f);

		ECS::Manager.AddComponent(entityid, transform);
	}
	void XMLSerializer::SaveTransform(XMLPrinter& printer, const ECS::EntityID entityid) {
		const Transform& transform = ECS::Manager.GetComponent<Transform>(entityid);
		printer.OpenElement("Transform");
		printer.PushAttribute("x", transform.Position.x);
		printer.PushAttribute("y", transform.Position.y);
		printer.PushAttribute("z", transform.Position.z);

		printer.PushAttribute("rx", transform.Rotation.x);
		printer.PushAttribute("ry", transform.Rotation.y);
		printer.PushAttribute("rz", transform.Rotation.z);

		printer.PushAttribute("sx", transform.Scale.x);
		printer.PushAttribute("sy", transform.Scale.y);
		printer.PushAttribute("sz", transform.Scale.z);
		printer.CloseElement();
	}

	// ENTITY NAME
	void XMLSerializer::SaveEntityName(XMLPrinter& printer, const ECS::EntityID entityid) {
		const EntityName& name = ECS::Manager.GetComponent<EntityName>(entityid);
		printer.OpenElement("EntityName");
		printer.PushAttribute("value", name.Value.c_str());
		printer.CloseElement();
	}
	void XMLSerializer::LoadEntityName(XMLElement* xEntityName, const ECS::EntityID entityid) {
		EntityName entityName;
		const char* name = xEntityName->Attribute("value");
		entityName.Value = std::string(name);
		ECS::Manager.AddComponent(entityid, entityName);
	}

	// CAMERA
	void XMLSerializer::SaveCamera(XMLPrinter& printer, const ECS::EntityID entityid) {
		if (!ECS::Manager.HasComponent<Camera>(entityid)) { return; }
		const Camera& camera = ECS::Manager.GetComponent<Camera>(entityid);
		printer.OpenElement("Camera");
		printer.CloseElement();
	}
	void XMLSerializer::LoadCamera(XMLElement* xCamera, const ECS::EntityID entityid) {
		Camera camera;
		ECS::Manager.AddComponent(entityid, camera);
	}

	// SPRITE RENDERER
	void XMLSerializer::SaveSpriteRenderer(XMLPrinter& printer, const ECS::EntityID entityid) {
		if (!ECS::Manager.HasComponent<SpriteRenderer>(entityid)) { return; }
		auto& renderer = ECS::Manager.GetComponent<SpriteRenderer>(entityid);

		printer.OpenElement("SpriteRenderer");
		printer.PushAttribute("name", renderer.TexName.c_str());
		printer.CloseElement();
	}
	void XMLSerializer::LoadSpriteRenderer(XMLElement* xSpriteRenderer, const ECS::EntityID entityid) {
		const char* name = xSpriteRenderer->Attribute("name");
		SpriteRenderer renderer(name);
		ECS::Manager.AddComponent(entityid, renderer);
	}

	// MESH RENDERER
	void XMLSerializer::SaveMeshRenderer(XMLPrinter& printer, const ECS::EntityID entityid) {
		if (!ECS::Manager.HasComponent<MeshRenderer>(entityid)) { return; }
		auto& renderer = ECS::Manager.GetComponent<MeshRenderer>(entityid);
		auto& material = renderer.Mesh.GetMaterial(); 

		printer.OpenElement("MeshRenderer");
		printer.PushAttribute("name", renderer.Name.c_str());

		printer.OpenElement("Material");
		printer.PushAttribute("ao", material.Ao);
		printer.PushAttribute("metallic", material.Metallic);
		printer.PushAttribute("roughness", material.Roughness);
		printer.PushAttribute("albedoR", material.Albedo.r);
		printer.PushAttribute("albedoG", material.Albedo.g);
		printer.PushAttribute("albedoB", material.Albedo.b);
		printer.CloseElement();

		printer.CloseElement();
	}
	void XMLSerializer::LoadMeshRenderer(XMLElement* xMeshRenderer, const ECS::EntityID entityid) {
		const char* name = xMeshRenderer->Attribute("name");
		MeshRenderer renderer(name);
		Material material;

		for (XMLElement* e = xMeshRenderer->FirstChildElement(); e != nullptr; e = e->NextSiblingElement()) {
			if (e->Value() == std::string("Material")) {
				material.Ao = e->FloatAttribute("ao");
				material.Metallic = e->FloatAttribute("metallic");
				material.Roughness = e->FloatAttribute("roughness");
				material.Albedo.x = e->FloatAttribute("albedoR");
				material.Albedo.y = e->FloatAttribute("albedoG");
				material.Albedo.z = e->FloatAttribute("albedoB");
				renderer.Mesh.SetMaterial(material);
				break;
			}			
		}

		ECS::Manager.AddComponent(entityid, renderer);
	}

	// MODEL RENDERER
	void XMLSerializer::SaveModelRenderer(XMLPrinter& printer, const ECS::EntityID entityid) {
		if (!ECS::Manager.HasComponent<ModelRenderer>(entityid)) { return; }
		const ModelRenderer& model = ECS::Manager.GetComponent<ModelRenderer>(entityid);
		printer.OpenElement("ModelRenderer");
		printer.PushAttribute("name", model.Name.c_str());
		printer.CloseElement();
	}
	void XMLSerializer::LoadModelRenderer(XMLElement* xModelRenderer, const ECS::EntityID entityid) {
		ModelRenderer model;
		const char* name = xModelRenderer->Attribute("name");
		model.Name = std::string(name);
		ECS::Manager.AddComponent(entityid, model);
	}

	// SPOT LIGHT 
	void XMLSerializer::SaveSpotLight(XMLPrinter& printer, const ECS::EntityID entityid) {
		if (!ECS::Manager.HasComponent<SpotLight>(entityid)) { return; }
		const SpotLight& light = ECS::Manager.GetComponent<SpotLight>(entityid);
		printer.OpenElement("SpotLight");
		printer.PushAttribute("colorR", light.Color.r);
		printer.PushAttribute("colorG", light.Color.g);
		printer.PushAttribute("colorB", light.Color.b);
		printer.PushAttribute("dirX", light.Direction.x);
		printer.PushAttribute("dirY", light.Direction.y);
		printer.PushAttribute("dirZ", light.Direction.z);
		printer.PushAttribute("intensity", light.Intensity);
		printer.CloseElement();
	}
	void XMLSerializer::LoadSpotLight(XMLElement* xLight, const ECS::EntityID entityid) {
		SpotLight light;
		light.Color.r = xLight->FloatAttribute("colorR");
		light.Color.g = xLight->FloatAttribute("colorG");
		light.Color.b = xLight->FloatAttribute("colorB");

		light.Direction.x = xLight->FloatAttribute("dirX");
		light.Direction.y = xLight->FloatAttribute("dirY");
		light.Direction.z = xLight->FloatAttribute("dirZ");

		light.Intensity = xLight->FloatAttribute("intensity");

		ECS::Manager.AddComponent(entityid, light);
	}

	// POINT LIGHT 
	void XMLSerializer::SavePointLight(XMLPrinter& printer, const ECS::EntityID entityid) {
		if (!ECS::Manager.HasComponent<PointLight>(entityid)) { return; }
		const PointLight& light = ECS::Manager.GetComponent<PointLight>(entityid);
		printer.OpenElement("PointLight");
		printer.PushAttribute("colorR", light.Color.r);
		printer.PushAttribute("colorG", light.Color.g);
		printer.PushAttribute("colorB", light.Color.b);
		printer.PushAttribute("intensity", light.Intensity);
		printer.CloseElement();
	}
	void XMLSerializer::LoadPointLight(XMLElement* xLight, const ECS::EntityID entityid) {
		PointLight light;
		light.Color.r = xLight->FloatAttribute("colorR");
		light.Color.g = xLight->FloatAttribute("colorG");
		light.Color.b = xLight->FloatAttribute("colorB");
		light.Intensity = xLight->FloatAttribute("intensity");
		ECS::Manager.AddComponent(entityid, light);
	}

	// DIRECTIONAL LIGHT 
	void XMLSerializer::SaveDirectionalLight(XMLPrinter& printer, const ECS::EntityID entityid) {
		if (!ECS::Manager.HasComponent<DirectionalLight>(entityid)) { return; }
		const DirectionalLight& light = ECS::Manager.GetComponent<DirectionalLight>(entityid);
		printer.OpenElement("DirectionalLight");
		printer.PushAttribute("colorR", light.Color.r);
		printer.PushAttribute("colorG", light.Color.g);
		printer.PushAttribute("colorB", light.Color.b);
		printer.PushAttribute("dirX", light.Direction.x);
		printer.PushAttribute("dirY", light.Direction.y);
		printer.PushAttribute("dirZ", light.Direction.z);
		printer.PushAttribute("intensity", light.Intensity);
		printer.CloseElement();
	}
	void XMLSerializer::LoadDirectionalLight(XMLElement* xLight, const ECS::EntityID entityid) {
		DirectionalLight light;
		light.Color.r = xLight->FloatAttribute("colorR");
		light.Color.g = xLight->FloatAttribute("colorG");
		light.Color.b = xLight->FloatAttribute("colorB");

		light.Direction.x = xLight->FloatAttribute("dirX");
		light.Direction.y = xLight->FloatAttribute("dirY");
		light.Direction.z = xLight->FloatAttribute("dirZ");

		light.Intensity = xLight->FloatAttribute("intensity");

		ECS::Manager.AddComponent(entityid, light);
	}

	// RIGIBODY
	void XMLSerializer::SaveRigidBody(XMLPrinter& printer, const ECS::EntityID entityid) {
		if (!ECS::Manager.HasComponent<RigidBody>(entityid)) { return; }
		const RigidBody& rigidbody = ECS::Manager.GetComponent<RigidBody>(entityid);
		printer.OpenElement("RigidBody");
		printer.PushAttribute("mass", rigidbody.Mass);
		printer.PushAttribute("gscale", rigidbody.GravityScale);

		printer.PushAttribute("Fx", rigidbody.Force.x);
		printer.PushAttribute("Fy", rigidbody.Force.y);
		printer.PushAttribute("Fz", rigidbody.Force.z);

		printer.PushAttribute("Dx", rigidbody.Drag.x);
		printer.PushAttribute("Dy", rigidbody.Drag.y);
		printer.PushAttribute("Dz", rigidbody.Drag.z);
		printer.CloseElement();
	}
	void XMLSerializer::LoadRigidBody(XMLElement* xRigidbody, const ECS::EntityID entityid) {
		RigidBody rigidbody;
		rigidbody.Mass = xRigidbody->FloatAttribute("mass");
		rigidbody.GravityScale = xRigidbody->FloatAttribute("gscale");

		rigidbody.Force.x = xRigidbody->FloatAttribute("Fx");
		rigidbody.Force.y = xRigidbody->FloatAttribute("Fy");
		rigidbody.Force.z = xRigidbody->FloatAttribute("Fz");

		rigidbody.Drag.x = xRigidbody->FloatAttribute("Dx");
		rigidbody.Drag.y = xRigidbody->FloatAttribute("Dy");
		rigidbody.Drag.z = xRigidbody->FloatAttribute("Dz");

		ECS::Manager.AddComponent(entityid, rigidbody);
	}
	// C#
	void XMLSerializer::SaveCsScript(XMLPrinter& printer, const ECS::EntityID entityid) {
#ifdef FRACTAL_CSHARP
		if (!ECS::Manager.HasComponent<CsScript>(entityid)) { return; }
		const CsScript& script = ECS::Manager.GetComponent<CsScript>(entityid);
		printer.OpenElement("CsScript");
		printer.PushAttribute("AssemblyPath", script.AssemblyPath.c_str());
		printer.PushAttribute("ClassName", script.ClassName.c_str());
		printer.CloseElement();
#endif
	}
	void XMLSerializer::LoadCsScript(XMLElement* xSharp, const ECS::EntityID entityid) {
#ifdef FRACTAL_CSHARP
		CsScript script;
		script.AssemblyPath = xSharp->Attribute("AssemblyPath");
		script.ClassName = xSharp->Attribute("ClassName");
		ECS::Manager.AddComponent(entityid, script);
#endif
	}
}