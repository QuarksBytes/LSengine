#ifndef __TEST_LUA_GRAPHICS_CPP__
#define __TEST_LUA_GRAPHICS_CPP__


#include <LuaGraphics/lua_graphics.cpp>


int main() {
    lua_State* L = luaL_newstate();
    luaL_openlibs(L);
    registerDrawingFunctions(L);

    // Load the script file
    if (luaL_dofile(L, "LuaGraphics/testGraphics.lua") != LUA_OK) {
        std::cerr << "Failed to load Lua script: " << lua_tostring(L, -1) << std::endl;
        return 1;
    }

   // Push function draw
   lua_getglobal(L, "draw");
   if (!lua_isfunction(L, -1)) {
       std::cerr << "`draw` is not a function" << std::endl;
       lua_close(L);
       return 1;
   }

   // Push viewPort with width and height
   int width = 800;
   int height = 600;
   lua_newtable(L); // Create a table

   lua_pushnumber(L, width);
   lua_setfield(L, -2, "width");

   lua_pushnumber(L, height);
   lua_setfield(L, -2, "height");


   //push pins states
    lua_newtable(L); // Create a table
    lua_pushboolean(L, false); // Pin 1 state
    lua_setfield(L, -2, "A0");

    lua_pushboolean(L, false); // Pin 2 state
    lua_setfield(L, -2, "A1");

   // Now call draw(viewPort)
   if (lua_pcall(L, 2, 0, 0) != LUA_OK) {
       std::cerr << "Error calling draw(): " << lua_tostring(L, -1) << std::endl;
   }


   lua_close(L);
   return 0;
}

#endif
