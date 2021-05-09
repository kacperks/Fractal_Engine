#pragma once

#include "Interpreter.h"

typedef std::string(Code)(std::string);

namespace FRL {
    class Lexer {
        public:
            void Begin(Code code);

            std::string RemoveWhitespace(std::string _whiteLine);

            // Reading Vars

            int GetInt(const char* name);
            bool GetBool(const char* name);
            std::string GetString(const char* name);

        private:
            
    };
}
