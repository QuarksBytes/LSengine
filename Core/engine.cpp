#ifndef __ENGINE_CPP__
#define __ENGINE_CPP__

#include"componant_parser.cpp"
#include"design_parser.cpp"
#include<vector>



class Engine{
    private:
       std::vector<Module> modules;
       std::vector<Module> runModulesQueue[2];
       uint32_t current=0;

   public:

    Engine(Design& design , ModuleRegistry& moduleRegistry){
       
        //adding all modules from design
        for(auto& component : design.components){
            modules.push_back(moduleRegistry.getModule(component.identity)); 
        }
       
        //reserving space for modulesQueue
        runModulesQueue[0].reserve(15);
        runModulesQueue[1].reserve(15);
    }

    void addModule(Module& m){
       modules.push_back(m);
    }
};


#endif