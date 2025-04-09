extern "C" {
    #include <lua5.4/lua.h>
    #include <lua5.4/lauxlib.h>
    #include <lua5.4/lualib.h>
}

#include <iostream>
#include <vector>


// C++ function exposed to Lua
int cpp_callback(lua_State* L) {
    // Get argument from Lua
    const char* msg = lua_tostring(L, 1);

    std::cout << "🔥 Callback from Lua! Message: " << msg << std::endl;

    // Return a string back to Lua
    lua_pushstring(L, "C++ says hi back!");

    return 1; // number of return values
}


int main() {
    lua_State* L = luaL_newstate();
    luaL_openlibs(L);

    // Register the C++ function in Lua as 'cpp_callback'
    lua_register(L, "cpp_callback", cpp_callback);

    // Load and run Lua script
    if (luaL_dofile(L, "script.lua") != LUA_OK) {
        std::cerr << "Lua error: " << lua_tostring(L, -1) << std::endl;
        lua_close(L);
        return 1;
    }

    lua_close(L);
    return 0;
}
