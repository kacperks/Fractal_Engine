#include <iostream>
#include <string>
#include "pch.h"

// include Lua, assumes it is local to this file
extern "C"
{
	#include "Vendor/LUA/include/lua.h"
	#include "Vendor/LUA/include/lauxlib.h"
	#include "Vendor/LUA/include/lualib.h"
}

#ifdef _WIN32
//#pragma comment(lib, "../Vendor/LUA/liblua53.a")
#endif

namespace fr {
	class LuaMan {
		public:
			void Initialize();
			
		private:

			// CHECK LUA FUNCTION

			bool CheckLua(lua_State* L, int r);

			int Test(lua_State* L);
	};
};