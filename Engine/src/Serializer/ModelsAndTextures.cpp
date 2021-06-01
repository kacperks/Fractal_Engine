
#include "pch.h"

#include "ModelsAndTextures.h"

namespace fr {
	void MTSerializer::SaveModelsAndTextures(const char* file) {
		FILE* pFile;
		fopen_s(&pFile, file, "w");
		tinyxml2::XMLPrinter printer(pFile);

		printer.PushHeader(true, true);
		printer.OpenElement("TexturesAndModels");


		printer.CloseElement();

		tinyxml2::XMLDocument document;
		document.Print(&printer);
		if (pFile != nullptr) { fclose(pFile); }
	}
}