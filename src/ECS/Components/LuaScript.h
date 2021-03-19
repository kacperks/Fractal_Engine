#include "../Systems/LuaSystem.h"
#include <thread>
#include <stdlib.h> 

// not finished yet

struct LuaScript : public ECS::BaseComponent {
    lua_State * L = lua_open();
    
    std::string file;
    void StartVoid(){
        luaL_openlibs(L);
    }
    void UpdateVoid(){
        for(;;){
            sleep(100);
        }
    }
    void Stop(){
         lua_close(L);
    }
};