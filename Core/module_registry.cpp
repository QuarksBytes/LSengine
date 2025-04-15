#ifndef __MODULE_REGISTRY_CPP__
#define __MODULE_REGISTRY_CPP__

#include "componant_parser.cpp"
#include <vector>
#include <string>
#include <iostream>
#include <map>

class ModuleRegistry {
    private:

     std::map<std::string, int> moduleMap;
     std::map<std::string, int> sourceMap;
     
    public:
     ModuleRegistry(std::vector<std::string> extensionSources){
            sources = extensionSources;
            for(auto source : extensionSources){
                try{
                 //converting to Module   
                ComponantParser::json j;
                source >> j;
                ComponantParser::Module m = j.get<ComponantParser::Module>();
                //adding to global vectors
                modulesMap[m.module] = m;
                //adding to source map
                sourceMap[m.module] = source;
                }
                catch(const std::exception& e){
                    std::cerr << "Error parsing JSON: " << e.what() << "\n";
                    return 1;
                }
            }
     }


      Module& getModule(const std::string& moduleName) {
          //TODO
          return modulesMap[moduleName];
      }

};


#endif