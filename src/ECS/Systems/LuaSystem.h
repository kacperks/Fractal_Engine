#pragma once

#include "../../fractal.hpp"

// not finished yet

#include <string>
#include <iostream>

extern "C"
{
    #include "../../vendor/LUA/include/lua.h"
    #include "../../vendor/LUA/include/lauxlib.h"
    #include "../../vendor/LUA/include/lualib.h"
}
#ifdef _WIN32
#pragma comment(lib, "../../vendor/LUA/liblua54.a")
#endif

using namespace std;
class LuaSystem : public ECS::BaseSystem{
    public :
        void Start(){

        }

        void Stop(){

        }

        void Update(){

        }
};