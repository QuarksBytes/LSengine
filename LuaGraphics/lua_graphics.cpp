#ifndef __LUA_GRAPHICS_CPP__
#define __LUA_GRAPHICS_CPP__

extern "C" {
    #include "lua.h"
    #include "lualib.h"
    #include "lauxlib.h"
  }

#include <iostream>

int drawCircle(lua_State* L) {
    double x = luaL_checknumber(L, 1);
    double y = luaL_checknumber(L, 2);
    double r = luaL_checknumber(L, 3);
    const char* color = luaL_checkstring(L, 4);

    std::cout << "Drawing circle at (" << x << ", " << y << ") with radius " << r
              << " and color " << color << "\n";
    return 0;
}

int drawRect(lua_State* L) {
    double x = luaL_checknumber(L, 1);
    double y = luaL_checknumber(L, 2);
    double w = luaL_checknumber(L, 3);
    double h = luaL_checknumber(L, 4);
    const char* color = luaL_checkstring(L, 5);

    std::cout << "Drawing rectangle at (" << x << ", " << y << ") with size "
              << w << "x" << h << " and color " << color << "\n";
    return 0;
}

int drawLine(lua_State* L) {
    double x1 = luaL_checknumber(L, 1);
    double y1 = luaL_checknumber(L, 2);
    double x2 = luaL_checknumber(L, 3);
    double y2 = luaL_checknumber(L, 4);
    const char* color = luaL_checkstring(L, 5);

    std::cout << "Drawing line from (" << x1 << ", " << y1 << ") to ("
              << x2 << ", " << y2 << ") with color " << color << "\n";
    return 0;
}


int setPin(lua_State* L) {
    const char* pinName = luaL_checkstring(L, 1);
    bool state = lua_toboolean(L, 2);
    std::cout << "Setting pin " << pinName << " to " << (state ? "HIGH" : "LOW") << "\n";
    return 0;
}

void registerDrawingFunctions(lua_State* L) {
    lua_register(L, "drawCircle", drawCircle);
    lua_register(L, "drawRect", drawRect);
    lua_register(L, "drawLine", drawLine);
    lua_register(L, "setPin", setPin);
}




#endif