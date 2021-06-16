
#pragma once

#include <TinyXML/tinyxml2.h>
#include "Core/ECS/Components.h"

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

		void LoadModels(const char* file);
		void LoadTxts(const char* file);

		void SaveModels(const char* file);
		void SaveTxts(const char* file);

	private:
		MTSerializer() = default;

		void LoadModel(XMLElement* xModel);
		void SaveModel(XMLPrinter &printer, std::string name, std::string path);

		void LoadTxt(XMLElement* xTXT);
		void SaveTxT(XMLPrinter &printer, std::string name, std::string path);
	};

	static MTSerializer& ModelsAndTxt = MTSerializer::Ref();
}