#pragma once

#include "pch.h"

#if defined(FR_LUA)
// not finished yet!

namespace fr {
	extern FRboolean CheckLua(lua_State* L, int r);
}

namespace fr{
	class LuaScripting {
		public:
			FRuint Init(std::string filename);

			lua_State* GetLuaState() const { return L; }
		private:
			func LuaStart();
			func LuaUpdate();

			lua_State* L;
			std::string CurrentScript;
	};
}

#endif