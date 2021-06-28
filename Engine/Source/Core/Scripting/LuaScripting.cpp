#include "pch.h"

#include "LuaScripting.h"

#if defined(FR_LUA)

namespace fr {
	FRboolean CheckLua(lua_State* L, int r) {
		if (r != LUA_OK) {
			std::string errormsg = lua_tostring(L, -1);
			UI.AddToConsole("[LUA Syntax error!] " + errormsg);
			return false;
		}
		return true;
	}
}

namespace fr {
	FRuint LuaScripting::Init(std::string filename) {
		L = luaL_newstate();

		luaL_openlibs(L);

		if (CheckLua(L, luaL_dofile(L, filename.c_str()))){

		}

		lua_close(L);
		return FR_NULL;
	}

	func LuaScripting::LuaStart() { return FR_NULL; }

	func LuaScripting::LuaUpdate(){ return FR_NULL; }
}

#endif