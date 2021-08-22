#pragma once

#include "MemoryFunctions.h"

#include <stdio.h>
#include <malloc.h>
#include <stdlib.h>
#include <string.h>

namespace fr {
	namespace Log {
		inline void ErrorLog(String log) { std::cout << termcolor::red << "[ERROR] " << log.CString() << termcolor::white << std::endl; }
		inline void WarnLog(String log) { std::cout << termcolor::bright_magenta << "[WARN] " << log.CString() << termcolor::white << std::endl; }
		inline void InfoLog(String log) {
		#ifndef FR_BULID
			std::cout << "[" << termcolor::bright_green << " OK " << "] " << termcolor::white << log.CString() << std::endl; 
		#endif
		}
	}
}

#define INFO(...) fr::Log::InfoLog(__VA_ARGS__)
#define ERROR(...) fr::Log::ErrorLog(__VA_ARGS__)
#define WARNING(...) fr::Log::WarnLog(__VA_ARGS__)