#include <iostream>
#include <string>

// not finished yet

// include Lua, assumes it is local to this file
extern "C"
{
	#include "../vendor/LUA/include/lua.h"
	#include "../vendor/LUA/include/lauxlib.h"
	#include "../vendor/LUA/include/lualib.h"
}

#ifdef _WIN32
#pragma comment(lib, "../vendor/LUA/liblua53.a")
#endif

namespace fr {
	class LuaMan {
		public:
			void Initialize();
			
		private:

			// CHECK LUA FUNCTION

			bool CheckLua(lua_State* L, int r);

			// HOST FUNTIONS

			int lua_HostFunction(lua_State* L);
	};
};