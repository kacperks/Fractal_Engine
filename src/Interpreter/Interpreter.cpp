#include "pch.h"

#include "Interpreter.h"

namespace FRL {
	void Interpreter::Initialize(std::string code) {
		Lexer::Start(code);
	};
};