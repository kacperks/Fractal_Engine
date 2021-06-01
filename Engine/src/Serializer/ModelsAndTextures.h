
#pragma once

#include <TinyXML/tinyxml2.h>
#include "ECS/Components.h"

namespace fr {

	using namespace tinyxml2;

	class MTSerializer {
	public:
		~MTSerializer() = default;
		MTSerializer(const MTSerializer&) = delete;
		MTSerializer& operator=(const MTSerializer&) = delete;
		static MTSerializer& Ref() {
			static MTSerializer reference;
			return reference;

		}

		void LoadModelsAndTextures(const char* file);
		void SaveModelsAndTextures(const char* file);

	private:
		MTSerializer() = default;

		void LoadModel(XMLElement* xModel);
		void SaveModel(XMLPrinter &printer, std::string name, std::string path);

		void LoadTxt(XMLElement* xTXT);
		void SaveTxT(XMLPrinter &printer, std::string name, std::string path);
	};

	static MTSerializer& ModelsAndTxt = MTSerializer::Ref();
}