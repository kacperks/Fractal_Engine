
#include "pch.h"

#include "ModelsAndTextures.h"

#include <TinyXML/tinyxml2.h>

namespace fr {
	
	using namespace tinyxml2;

	void MTSerializer::SaveModelsAndTextures(const char* file) {}

	void MTSerializer::SaveModel(XMLPrinter& printer, std::string name, std::string path){
		printer.OpenElement("Model");
		printer.PushAttribute("Name", name.c_str());
		printer.PushAttribute("Path", path.c_str());
		printer.CloseElement();
	}

	void MTSerializer::LoadModel(XMLElement* xModel) {
		const char* Name = xModel->Attribute("Name");
		const char* Path = xModel->Attribute("Name");
		Resource.LoadModel(Name, Path);
	}

	void MTSerializer::SaveTxT(XMLPrinter& printer, std::string name, std::string path) {
		printer.OpenElement("Texture");
		printer.PushAttribute("Name", name.c_str());
		printer.PushAttribute("Path", path.c_str());
		printer.CloseElement();
	}

	void MTSerializer::LoadTxt(XMLElement* xTXT) {
		const char* Name = xTXT->Attribute("Name");
		const char* Path = xTXT->Attribute("Name");
		Resource.AddTex2D(Name, Resource.LoadTex2D(Path));
	}

}