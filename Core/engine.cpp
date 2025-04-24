#ifndef __ENGINE_CPP__
#define __ENGINE_CPP__

#include<vector>

#include"Parser/component_parser.cpp"
#include"Parser/design_parser.cpp"
#include"Error/ls_error.cpp"
#include"Lua/lua.cpp"

#define FLAGS_ENGINE_STARTED 1

class Engine{
private:

  Lua luaLogical;
  Lua luaElectrical;

  std::vector<ComponentParser:: Componant> logicalModules;
  std::vector<uint32_t> runModulesList[2];

  uint32_t current=0;

  uint32_t flags=0;


public:


  /*
   *
   *
   * Needs Complete rewriting
   * after thinking of design pattern
   *
  Engine(Design& design , ModuleRegistry& moduleRegistry){

    //adding all modules from design
    for(auto& component : design.components){
      modules[component.id] = moduleRegistry.getModule(component.identity);
    }

    //reserving space for modulesQueue
    runModulesList[0].reserve(15);
    runModulesList[1].reserve(15);

    //prepering first run queue , only componant eith type input is to be in run queue 1
    for(auto& module : modules){
      if(module.type == "input"){
        runModulesList[0].push_back(module);
      }
    }


  }

  */



/*
 *
 * returns id for accessing the elements in engine again ,
 * id can never be 0,
 * if it is 0 then an error has occured
 *
 */
  uint32_t addModuleForLogical(ComponentParser::Componant& m){
    if(flags&FLAGS_ENGINE_STARTED){
      LSError::SetError("Engine has already started, cannot add more modules");
      return 0;
    }

    if(!m.logic_simulation){
      LSError::SetError("Doesn't contain logical logic");
      return 0;
    }

    logicalModules.push_back(m);
    // convert lua template into function and add it to luaLogical.load
    //luaLogical.load(moduleLogicalFunction);

    return logicalModules.size();
  }

  ComponentParser::Componant* operator[](uint32_t id){
    if(!id || id>logicalModules.size()){
      LSError::SetError("Invalid module id");
      return nullptr;
    }
    return &logicalModules[id-1];
  }


  void runLogical(){
    //TODO
    //run the modules in the current queue and add the output modules to the next queue
    //after running all modules in the current queue, swap the queues and repeat until no more modules to run

    std::vector<ComponentParser::Componant>& moduleList=logicalModules;
    std::vector<uint32_t>& currentList=runModulesList[(current&1)];

    ComponentParser::Componant* cmodule=nullptr;

    Lua& lua=luaLogical;

    while(currentList.size()){ // loop as long as there is element in current list

      for (const uint32_t& value: currentList){
        cmodule=&moduleList[value];
        lua.loadFunction(cmodule->logic_simulation->functionName);
        //  for
      }

      current^=1;
      currentList.resize(0);
      currentList=runModulesList[(current&1)];
    }
  }
};

#undef FLAGS_ENGINE_STARTED

#endif
