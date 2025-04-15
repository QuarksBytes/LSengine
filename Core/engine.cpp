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

        //prepering first run queue , only componant eith type input is to be in run queue 1
        for(auto& module : modules){
            if(module.type == "input"){
                runModulesQueue[0].push_back(module);
            }
        }


    }

    void addModule(Module& m){
       modules.push_back(m);
    }


    void run(){
        //TODO
        //run the modules in the current queue and add the output modules to the next queue
        //after running all modules in the current queue, swap the queues and repeat until no more modules to run
        for(auto& module : runModulesQueue[current]){
            //run module
        }
        current = (current + 1) % 2;
    }
};


#endif