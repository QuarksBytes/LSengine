#include"Lua/lua.cpp"


LuaCallback_function(myFunction){
  std::cout<<"Function registration is working\n";
  return 0;
}

int main(){
  Lua lua;
  lua.open("Test/Lua/test.lua");
  // lua.run();

  if(lua.loadFunction("greet")){
    lua<<" LSEngine "<<10<<22<<45;
    lua.call();
  }

  lua.registerFunction("myFunc",myFunction);

  if(lua.loadFunction("myFunc")){
    lua<<"OOps";
    lua.call();
  }
  
  lua.open("Test/Lua/test.lua");
  lua.registerFunction("cpp_callback",myFunction);

  if(lua.loadFunction("myFunc")){
    lua<<"Hello from C++ to Lua to C++!";
    lua.call();
  }
}
