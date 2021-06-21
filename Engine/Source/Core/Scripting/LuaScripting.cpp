#include "pch.h"

#include "LuaScripting.h"

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
			lua_getglobal(L, "A");
			if (lua_isnumber(L, -1)) std::cout << "[CPP S1] a = " << (int)lua_tointeger(L, -1) << std::endl;
		}

		lua_close(L);
		return FR_NULL;
	}

	func LuaScripting::LuaStart() { return FR_NULL; }

	func LuaScripting::LuaUpdate(){ return FR_NULL; }
}