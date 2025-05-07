#ifndef __ENGINE_CPP__
#define __ENGINE_CPP__

#include<vector>
#include<cstdint>

#include"Componant.cpp"
#include"Parser/design_parser.cpp"
#include"Error/ls_error.cpp"
#include"Lua/lua.cpp"

#define FLAGS_ENGINE_STARTED 1

enum ModulaInputState{
  MODULE_STATE_INCOMPLETE,
  MODULE_STATE_COMPLETE,
  MODULE_STATE_ERROR
};

struct ModuleState{
  Componant* componant;
  ModulaInputState state;
};

class Engine{
private:

  Lua luaLogical;
  Lua luaElectrical;

  std::vector<Componant> componants;

  //buffer list to  run
  std::list<ModuleState> runModulesList[2];

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
  uint32_t addModuleForLogical(Componant& m){
    if(flags&FLAGS_ENGINE_STARTED){
      LSError::SetError("Engine has already started, cannot add more modules");
      return 0;
    }

    if(m.logicSimulator.pins.size()==0){
      LSError::SetError("Doesn't contain logical logic");
      return 0;
    }

    componants.push_back(m);
    // convert lua template into function and add it to luaLogical.load
    //luaLogical.load(moduleLogicalFunction);

    return componants.size();
  }

  Componant* operator[](uint32_t id){
    if(!id || id>componants.size()){
      LSError::SetError("Invalid module id");
      return nullptr;
    }
    return &componants[id-1];
  }



  std::list<Componant&> runModule(Componant* module){
    

    std::list<Componant&> outputModules;
    
    //TODO

    return outputModules;

  }


  void runLogical(){
    //TODO
    //run the modules in the current queue and add the output modules to the next queue
    //after running all modules in the current queue, swap the queues and repeat until no more modules to run

    int currentRunningListIndex=0;

    //fill the first run queue with the input modules
    for(auto& module : componants){
      if(module.type == INPUT){
        ModuleState state;
        state.componant = &module; // Assign the address of the module
        state.state = MODULE_STATE_INCOMPLETE;
        runModulesList[currentRunningListIndex].push_back(state);
      }
    }

    while(runModulesList[currentRunningListIndex].size() >0){ // loop as long as there is element in current list

         for(auto& moduleState : runModulesList[currentRunningListIndex]){
          //run compoannt if it has all input group is completed
            if(moduleState.state == MODULE_STATE_COMPLETE){
              // run the module at current running list
              auto forwardedComponants = runModule(moduleState.componant);
             //moving new componants to the next running list
              runModulesList[currentRunningListIndex^1].insert(
              runModulesList[currentRunningListIndex^1].end(),
              forwardedComponants.begin(),
              forwardedComponants.end()
          );
        }

      }// end of running list modules
      
      currentRunningListIndex^=1; // swap the running list index
      runModulesList[currentRunningListIndex].clear(); // clear the current running list

     }




  }






};

#undef FLAGS_ENGINE_STARTED

#endif
