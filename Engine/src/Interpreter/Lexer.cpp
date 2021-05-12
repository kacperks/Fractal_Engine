#include "pch.h"

#include "Lexer.h"

namespace FRL {
	void Lexer::Begin(std::string code) {
		std::stringstream fileStream(code);
		std::string segment;
		int lineNumber = 0;

		while (std::getline(fileStream, segment, '\n')) {

			lineNumber++;

			if (segment.rfind("print") == 0 || segment.empty()) {

			}

			else if (segment.find(":")) {

			}
		}
	}
}
