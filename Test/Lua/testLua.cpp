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

  lua.load("print('Hello from C++ to Lua!')");

  lua.load(R"(
    function test1()
      print("Hello test1 from Lua!")
    end
    )");

    lua.load(R"(
      function test1()
        print("Hello test2 from Lua!")
      end
      )");
  
    if(lua.loadFunction("test1")){
      lua.call();
    }


    if(lua.loadFunction("greet")){
      std::cout<<"It's working\n";
      lua<<"Shubham"<<1<<2<<3;
      lua.call();
    }else{
      std::cout<<"It's not working\n";

    }

  }
