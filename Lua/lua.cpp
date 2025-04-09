#ifndef __LSENGINE_LUA_LANG__
#define __LSENGINE_LUA_LANG__

#include<cstdint>
#include<iostream>
#include<string>


#define LuaCallback_function(x) int x(lua_State* state)

extern "C" {
  #include "lua.h"
  #include "lualib.h"
  #include "lauxlib.h"
}

class Lua{
private:

  lua_State* state=NULL;
  uint32_t functionArgumentCount=0;

  void newState(){
    if(!(state=luaL_newstate())){
      std::cerr<<"[ Error ] : Lua initialization error\n"; // add alternative method which does not exit on error
      std::exit(EXIT_FAILURE);
    }
    luaL_openlibs(state);
  }

public:



  bool open(const std::string& text){
    if (luaL_dofile(state, text.c_str()) != LUA_OK) {
      std::cerr<<"[ Error ] : "<<lua_tostring(state,-1)<<std::endl;
      lua_pop(state, 1);
      return false;
    }
    return true;
  }

  bool load(const std::string& luaScript){
    if (luaL_dostring(state, luaScript.c_str())!=LUA_OK) {
      std::cerr << "Lua error: " << lua_tostring(state, -1) << std::endl;
      lua_pop(state, 1);
      return false;
    }
  }


  bool loadFunction(const std::string& funcName){
    lua_getglobal(state, funcName.c_str());

    if (!lua_isfunction(state, -1)) {
      std::cerr<<funcName.c_str()<< " is not a function or doesn't exist!" << std::endl;
      lua_pop(state, 1);
      return false;
    }

    functionArgumentCount=0;
    return true;

  }


  Lua& operator<<(bool val){
    if(true){
      lua_pushboolean(state,1);
    }else{
      lua_pushboolean(state,0);
    }
    ++functionArgumentCount;
    return *this;
  }

  Lua& operator<<(int32_t val){
    lua_pushinteger(state,val);
    ++functionArgumentCount;
    return *this;
  }

  Lua& operator<<(double val){
    lua_pushnumber(state,val);
    ++functionArgumentCount;
    return *this;
  }

  Lua& operator<<(float val){
    lua_pushnumber(state,(double)val);
    ++functionArgumentCount;
    return *this;
  }

  Lua& operator<<(const char* str){
    lua_pushstring(state,str);
    ++functionArgumentCount;
    return *this;
  }

  Lua& operator<<(const void* add){
    lua_pushnil(state);
    return *this;
  }


  void call(){
    lua_pcall(state, functionArgumentCount, 0, 0);
  }

  void registerFunction(const char* fname,int (*func)(lua_State* )){
    lua_register(state,fname,func);
  }

  Lua(){
    newState();
  }

  ~Lua(){
    lua_close(state);
  }
};


#endif
