#include "pch.h"
#include "SceneSerializer.h"
#include "Scene/EntityManager.h"

namespace fr {

	// SCENE
	void SceneSerializer::LoadScene(const char* filename) {
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
		}
	}
	void SceneSerializer::SaveScene(const char* filename) {
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
	void SceneSerializer::LoadEntity(XMLElement* xEntity, const ECS::EntityID entityid) {
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
		}
	}
	void SceneSerializer::SaveEntity(XMLPrinter& printer, const ECS::EntityID entityid) {
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
		printer.CloseElement();
	}

	// TRANSFORM
	void SceneSerializer::LoadTransform(XMLElement* xTransform, const ECS::EntityID entityid) {
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
	void SceneSerializer::SaveTransform(XMLPrinter& printer, const ECS::EntityID entityid) {
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
	void SceneSerializer::SaveEntityName(XMLPrinter& printer, const ECS::EntityID entityid) {
		const EntityName& name = ECS::Manager.GetComponent<EntityName>(entityid);
		printer.OpenElement("EntityName");
		printer.PushAttribute("value", name.Value.c_str());
		printer.CloseElement();
	}
	void SceneSerializer::LoadEntityName(XMLElement* xEntityName, const ECS::EntityID entityid) {
		EntityName entityName;
		const char* name = xEntityName->Attribute("value");
		entityName.Value = std::string(name);
		ECS::Manager.AddComponent(entityid, entityName);
	}

	// CAMERA
	void SceneSerializer::SaveCamera(XMLPrinter& printer, const ECS::EntityID entityid) {
		if (!ECS::Manager.HasComponent<Camera>(entityid)) { return; }
		const Camera& camera = ECS::Manager.GetComponent<Camera>(entityid);
		printer.OpenElement("Camera");
		printer.CloseElement();
	}
	void SceneSerializer::LoadCamera(XMLElement* xCamera, const ECS::EntityID entityid) {
		Camera camera;
		ECS::Manager.AddComponent(entityid, camera);
	}

	// SPRITE RENDERER
	void SceneSerializer::SaveSpriteRenderer(XMLPrinter& printer, const ECS::EntityID entityid) {
		if (!ECS::Manager.HasComponent<SpriteRenderer>(entityid)) { return; }
		auto& renderer = ECS::Manager.GetComponent<SpriteRenderer>(entityid);

		printer.OpenElement("SpriteRenderer");
		printer.PushAttribute("name", renderer.TexName.c_str());
		printer.CloseElement();
	}
	void SceneSerializer::LoadSpriteRenderer(XMLElement* xSpriteRenderer, const ECS::EntityID entityid) {
		const char* name = xSpriteRenderer->Attribute("name");
		SpriteRenderer renderer(name);
		ECS::Manager.AddComponent(entityid, renderer);
	}

	// MESH RENDERER
	void SceneSerializer::SaveMeshRenderer(XMLPrinter& printer, const ECS::EntityID entityid) {
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
	void SceneSerializer::LoadMeshRenderer(XMLElement* xMeshRenderer, const ECS::EntityID entityid) {
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
	void SceneSerializer::SaveModelRenderer(XMLPrinter& printer, const ECS::EntityID entityid) {
		if (!ECS::Manager.HasComponent<ModelRenderer>(entityid)) { return; }
		const ModelRenderer& model = ECS::Manager.GetComponent<ModelRenderer>(entityid);
		printer.OpenElement("ModelRenderer");
		printer.PushAttribute("name", model.Name.c_str());
		printer.CloseElement();
	}
	void SceneSerializer::LoadModelRenderer(XMLElement* xModelRenderer, const ECS::EntityID entityid) {
		
		const char* name = xModelRenderer->Attribute("name");
		ModelRenderer model = ModelRenderer(name);
		ECS::Manager.AddComponent(entityid, model);
	}

	// SPOT LIGHT 
	void SceneSerializer::SaveSpotLight(XMLPrinter& printer, const ECS::EntityID entityid) {
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
	void SceneSerializer::LoadSpotLight(XMLElement* xLight, const ECS::EntityID entityid) {
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
	void SceneSerializer::SavePointLight(XMLPrinter& printer, const ECS::EntityID entityid) {
		if (!ECS::Manager.HasComponent<PointLight>(entityid)) { return; }
		const PointLight& light = ECS::Manager.GetComponent<PointLight>(entityid);
		printer.OpenElement("PointLight");
		printer.PushAttribute("colorR", light.Color.r);
		printer.PushAttribute("colorG", light.Color.g);
		printer.PushAttribute("colorB", light.Color.b);
		printer.PushAttribute("intensity", light.Intensity);
		printer.CloseElement();
	}
	void SceneSerializer::LoadPointLight(XMLElement* xLight, const ECS::EntityID entityid) {
		PointLight light;
		light.Color.r = xLight->FloatAttribute("colorR");
		light.Color.g = xLight->FloatAttribute("colorG");
		light.Color.b = xLight->FloatAttribute("colorB");
		light.Intensity = xLight->FloatAttribute("intensity");
		ECS::Manager.AddComponent(entityid, light);
	}

	// DIRECTIONAL LIGHT 
	void SceneSerializer::SaveDirectionalLight(XMLPrinter& printer, const ECS::EntityID entityid) {
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
	void SceneSerializer::LoadDirectionalLight(XMLElement* xLight, const ECS::EntityID entityid) {
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
	void SceneSerializer::SaveRigidBody(XMLPrinter& printer, const ECS::EntityID entityid) {
		if (!ECS::Manager.HasComponent<RigidBody>(entityid)) { return; }
		const RigidBody& rigidbody = ECS::Manager.GetComponent<RigidBody>(entityid);
		printer.OpenElement("RigidBody");
		printer.PushAttribute("mass", rigidbody.Mass);
		printer.CloseElement();
	}
	void SceneSerializer::LoadRigidBody(XMLElement* xRigidbody, const ECS::EntityID entityid) {
		RigidBody rigidbody;
		rigidbody.Mass = xRigidbody->FloatAttribute("mass");

		ECS::Manager.AddComponent(entityid, rigidbody);
	}
	// C#

	void SceneSerializer::SaveModel(XMLPrinter& printer, std::string name, std::string path) {
		printer.OpenElement("Model");
		printer.PushAttribute("Name", name.c_str());
		printer.PushAttribute("Path", path.c_str());
		printer.CloseElement();
	}

	void SceneSerializer::LoadModel(XMLElement* xModel) {
		const char* Name = xModel->Attribute("Name");
		const char* Path = xModel->Attribute("Name");
		Resource.LoadModel(Name, Path);
	}

	void SceneSerializer::SaveTxT(XMLPrinter& printer, std::string name, std::string path) {
		printer.OpenElement("Texture");
		printer.PushAttribute("Name", name.c_str());
		printer.PushAttribute("Path", path.c_str());
		printer.CloseElement();
	}

	void SceneSerializer::LoadTxt(XMLElement* xTXT) {
		const char* Name = xTXT->Attribute("Name");
		const char* Path = xTXT->Attribute("Name");
		Resource.AddTex2D(Name, Resource.LoadTex2D(Path));
	}
}