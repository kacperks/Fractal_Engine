#pragma once

#include "pch.h"

// not finished yet!

namespace fr {
	bool CheckLua(lua_State* L, int r){
		if (r != LUA_OK){
			std::string errormsg = lua_tostring(L, -1);
			UI.AddToConsole("[LUA Syntax error!] " + errormsg);
			return false;
		}
		return true;
	}

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