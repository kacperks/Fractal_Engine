#pragma once

#include <TinyXML2/tinyxml2.h>
#include "Core/ECS/Components.h"

namespace fr {

	using namespace tinyxml2;

	class XMLSerializer {
	public:		
		~XMLSerializer() = default;
		XMLSerializer(const XMLSerializer&) = delete;
		XMLSerializer& operator=(const XMLSerializer&) = delete;
		static XMLSerializer& Ref() {
			static XMLSerializer reference;
			return reference;
		}

		// Scene stuff
		void SaveScene(const char* filename);
		void LoadScene(const char* filename);


		void LoadModels(const char* file);
		void LoadTxts(const char* file);

		void SaveModels(const char* file);
		void SaveTxts(const char* file);


	private:
		XMLSerializer() = default;

		// ENTITY
		void SaveEntity(XMLPrinter& printer, const ECS::EntityID entityid);
		void LoadEntity(XMLElement* xEntity, const ECS::EntityID entityid);

		// TRANSFORM
		void SaveTransform(XMLPrinter& printer, const ECS::EntityID entityid);
		void LoadTransform(XMLElement* xTransform, const ECS::EntityID entityid);

		// ENTITY NAME
		void SaveEntityName(XMLPrinter& printer, const ECS::EntityID entityid);
		void LoadEntityName(XMLElement* xEntityName, const ECS::EntityID entityid);

		// CAMERA
		void SaveCamera(XMLPrinter& printer, const ECS::EntityID entityid);
		void LoadCamera(XMLElement* xCamera, const ECS::EntityID entityid);

		// SPRITE RENDERER
		void SaveSpriteRenderer(XMLPrinter& printer, const ECS::EntityID entityid);
		void LoadSpriteRenderer(XMLElement* xSpriteRenderer, const ECS::EntityID entityid);

		// MESH RENDERER
		void SaveMeshRenderer(XMLPrinter& printer, const ECS::EntityID entityid);
		void LoadMeshRenderer(XMLElement* xMeshRenderer, const ECS::EntityID entityid);

		// MODEL RENDERER
		void SaveModelRenderer(XMLPrinter& printer, const ECS::EntityID entityid);
		void LoadModelRenderer(XMLElement* xModelRenderer, const ECS::EntityID entityid);

		// SPOT LIGHT
		void SaveSpotLight(XMLPrinter& printer, const ECS::EntityID entityid);
		void LoadSpotLight(XMLElement* xLight, const ECS::EntityID entityid);

		// POINT LIGHT
		void SavePointLight(XMLPrinter& printer, const ECS::EntityID entityid);
		void LoadPointLight(XMLElement* xLight, const ECS::EntityID entityid);

		// DIRECTIONAL LIGHT
		void SaveDirectionalLight(XMLPrinter& printer, const ECS::EntityID entityid);
		void LoadDirectionalLight(XMLElement* xLight, const ECS::EntityID entityid);

		// DIRECTIONAL LIGHT
		void SaveRigidBody(XMLPrinter& printer, const ECS::EntityID entityid);
		void LoadRigidBody(XMLElement* xRigidbody, const ECS::EntityID entityid);

		// Models And Txt's

		void LoadModel(XMLElement* xModel);
		void SaveModel(XMLPrinter& printer, std::string name, std::string path);

		void LoadTxt(XMLElement* xTXT);
		void SaveTxT(XMLPrinter& printer, std::string name, std::string path);
	};

	static XMLSerializer& Serializer = XMLSerializer::Ref();
}