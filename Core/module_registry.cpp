#ifndef __MODULE_REGISTRY_CPP__
#define __MODULE_REGISTRY_CPP__

#include "Parser/componant_parser.cpp"
#include <vector>
#include <string>
#include <iostream>
#include <map>

class ModuleRegistry {
    
    public:
    
     std::map<std::string, ComponantParser::Module> moduleMap;
     std::map<std::string, std::string> sourceMap;
     
    
     ModuleRegistry(std::vector<std::string> extensionSources){
            
            for(auto source : extensionSources){
                try{
                 //converting to Module   
                ComponantParser::json j = ComponantParser::json::parse(source);
                ComponantParser::Module m = j.get<ComponantParser::Module>();
                //adding to global vectors
                moduleMap[m.module] = m;
                //adding to source map
                sourceMap[m.module] = source;
                }
                catch(const std::exception& e){
                    std::cerr << "Error parsing JSON: " << e.what() << "\n";
                }
            }
     }


     ComponantParser::Module& getModule(const std::string& moduleName) {
          //TODO
          return moduleMap[moduleName];
      }

};


#endif