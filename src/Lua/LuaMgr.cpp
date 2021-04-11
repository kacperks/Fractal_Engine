#include "LuaMgr.hpp"

namespace fr {

    std::string ProjName,Version,StartScene,ModelName,ModelPath;

	// MAIN

	bool LuaMan::CheckLua(lua_State* L, int r) 
	{
		if (r != LUA_OK)
		{
			std::string errormsg = lua_tostring(L, -1);
			std::cout << errormsg << std::endl;
			return false;
		}
		return true;
	}

	void LuaMan::Initialize(const char* name) {
		// Create Lua State
		lua_State* L = luaL_newstate();

		// Add standard libraries to Lua Virtual Machine
		luaL_openlibs(L);

		if (CheckLua(L, luaL_dofile(L, name))) {
			
		}
	}
};