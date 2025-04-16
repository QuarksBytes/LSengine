#ifndef __ENGINE_CPP__
#define __ENGINE_CPP__

#include"Parser/componant_parser.cpp"
#include"Parser/design_parser.cpp"
#include<vector>
#include<map>


class Engine{
    private:
       std::map<int ,ComponantParser:: Module> modules;
       std::vector<ComponantParser::Module> runModulesQueue[2];
       uint32_t current=0;

   public:

    Engine(Design& design , ModuleRegistry& moduleRegistry){
       
        //adding all modules from design
        for(auto& component : design.components){
            modules[component.id] = moduleRegistry.getModule(component.identity);
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