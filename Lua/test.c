extern "C" {
    #include <lua5.4/lua.h>
    #include <lua5.4/lauxlib.h>
    #include <lua5.4/lualib.h>
}

#include <iostream>

int main() {
    lua_State* L = luaL_newstate();
    luaL_openlibs(L);

    if (luaL_dostring(L, "print('Hello from Lua!')")) {
        std::cerr << "Lua error: " << lua_tostring(L, -1) << std::endl;
    }

    lua_close(L);
    return 0;
}
