#ifndef __ENGINE_CPP__
#define __ENGINE_CPP__

#include"componant_parser.cpp"
#include<vector>

class Engine{
    private:
       std::vector<Module> modulesQueue[2];
       uint32_t current=0;

   public:

    Engine(){
        modulelesQueue[0].reserve(15);
        modulelesQueue[1].reserve(15);
    }

    void addModule(Module& m){
        modulesQueue[current^1].push_back(m);
        
    }
};


#endif