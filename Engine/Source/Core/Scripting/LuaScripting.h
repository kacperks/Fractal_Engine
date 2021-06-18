#pragma once

#include "pch.h"

// not finished yet!

namespace fr {
	extern FRboolean CheckLua(lua_State* L, int r);
}

namespace fr{
	class LuaScripting {
		public:
			FRuint Init();
			
			FRuint InitScript(std::string filename);
		private:
			lua_State* L = luaL_newstate();

			func LuaStart();
			func LuaUpdate();
	};
}