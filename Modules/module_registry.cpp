#ifndef __MODULE_REGISTRY_CPP__
#define __MODULE_REGISTRY_CPP__

#include <vector>
#include <string>
#include <iostream>
#include <map>

#include "Parser/component_parser.cpp"

struct __Module__Internal__{
  ComponentParser::Module module;
  std::string source;
};

class ModuleRegistry {
private:
  std::map<std::string,__Module__Internal__> moduleMap;

public:



  ModuleRegistry(){

  }

  ModuleRegistry(std::vector<std::string> extensionSources){

    __Module__Internal__ minternal;
    for(auto source : extensionSources){
      try{
        //converting to Module
        ComponentParser::json j = ComponentParser::json::parse(source);
        //adding to global vectors
        __Module__Internal__ minternal=(__Module__Internal__){
          .module=j.get<ComponentParser::Module>(),
          .source=source
        };
        moduleMap[minternal.module.module]=minternal;
      }
      catch(const std::exception& e){
        std::cerr << "Error parsing JSON: " << e.what() << "\n";
      }
    }
  }

  void add(std::string source){
    try{
      //converting to Module
      ComponentParser::json j = ComponentParser::json::parse(source);
      //adding to global vectors
      __Module__Internal__ minternal=(__Module__Internal__){
        .module=j.get<ComponentParser::Module>(),
        .source=source
      };
      moduleMap[minternal.module.module]=minternal;
    }
    catch(const std::exception& e){
      std::cerr << "Error parsing JSON: " << e.what() << "\n";
    }
  }

  ComponentParser::Module& getModule(const std::string& key){
    return moduleMap[key].module;
  }

  std::string& getSource(const std::string& key){
    return moduleMap[key].source;
  }


};


#endif
