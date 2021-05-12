#pragma once



#include "Interpreter.h"

typedef std::string(Code)(std::string);

namespace FRL {
    class Lexer {
        public:
            /*
            ~Lexer();
            Lexer(const Lexer&) = delete;
            Lexer& operator=(const Lexer&) = delete;

            static Lexer& Ref() {
                static Lexer reference;
                return reference;
            }
            */

            void Begin(std::string code);

            // Reading Vars

            int GetInt(const char* name , std::string code);
            bool GetBool(const char* name , std::string code);
            std::string GetString(const char* name , std::string code);

        private:
            Lexer();
    };
   // static Lexer& lexer = Lexer::Ref();
}
