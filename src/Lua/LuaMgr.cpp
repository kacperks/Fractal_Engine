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

	void LuaMan::Initialize() {
		// Create Lua State
		lua_State* L = luaL_newstate();

		// Add standard libraries to Lua Virtual Machine
		luaL_openlibs(L);

		if (CheckLua(L, luaL_dofile(L, "Resource/ProjectSettings.lua"))) {
			LoadInfo(L);
		}
	}

    void LuaMan::LoadInfo(lua_State* L) {
            LoadProjectInfo(L);
            LoadModelsInfo(L);
    }

	void LuaMan::LoadProjectInfo(lua_State* L) {

		lua_getglobal(L, "Name");
		if (lua_isstring(L, -1)) ProjName = lua_tostring(L, -1);

        lua_getglobal(L, "Version");
		if (lua_isstring(L, -1)) Version = lua_tostring(L, -1);

        lua_getglobal(L, "StartScene");
		if (lua_isstring(L, -1)) StartScene = lua_tostring(L, -1);

	}

    void LuaMan::LoadModelsInfo(lua_State* L){
        lua_getglobal(L, "ModelName");
		if (lua_isstring(L, -1)) ModelName = lua_tostring(L, -1);

        lua_getglobal(L, "ModelPath");
		if (lua_isstring(L, -1)) ModelPath = lua_tostring(L, -1);
    }

    void LuaMan::LoadScriptsInfo(lua_State* L){
        // not finished yet
    }
};