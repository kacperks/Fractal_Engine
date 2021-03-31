#pragma once

//#include "../../../fractal.hpp"
#include "../Bulid.hpp"

namespace bulid {
	class Win32 {
		public:
			void BulidAll();
		private:
			void BulidCSM(const char* location);
			void BulidCpp(const char* location);
			void BulidGLSL(const char* location);
	};
};