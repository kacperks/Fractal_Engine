#pragma once

// not finished yet
// i want to make custom a scripting language


#include <set>
#include <map>
#include <array>
#include <tuple>
#include <queue>
#include <vector>
#include <string>
#include <bitset>
#include <stdio.h>
#include <memory>
#include <cassert>
#include <sstream>
#include <fstream>
#include <iostream>
#include <typeinfo>
#include <algorithm>
#include <functional>
#include <filesystem>
#include <unordered_map>

#include "Lexer.h"


namespace FRL {
	class Interpreter {
		public:
			/*
			~Interpreter();

			Interpreter(const Interpreter&) = delete;
			Interpreter& operator=(const Interpreter&) = delete;

			static Interpreter& Ref() {
				static Interpreter reference;
				return reference;
			}
			*/

			void Initialize(std::string code);

		private:
			Interpreter();
	};
	
	//static Interpreter& FractalScript = Interpreter::Ref();
};