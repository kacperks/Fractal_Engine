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
	FRuint LuaScripting::Init() {
		return FR_NULL;
	}

	FRuint LuaScripting::InitScript(std::string filename) {
		return FR_NULL;
	}
}