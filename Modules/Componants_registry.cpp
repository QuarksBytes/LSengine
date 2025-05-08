#ifndef __MODULE_REGISTRY_CPP__
#define __MODULE_REGISTRY_CPP__

#include <vector>
#include <string>
#include <iostream>
#include <map>

#include "Parser/component_parser.cpp"


class ComponantRegistry {
private:
  std::map<std::string,Parser::ComponantParsed> componantMap;

public:

  // Add a component to the registry
  void addComponant(const Parser::ComponantParsed& componant) {
    componantMap[componant.name] = componant;
  }

  // Get a component by its name
  Parser::ComponantParsed getComponant(const std::string& name) {
    if (componantMap.find(name) != componantMap.end()) {
      return componantMap[name];
    } else {
      throw std::runtime_error("Component not found in registry.");
    }
  }

  // List all components in the registry
  void listComponants() {
    for (const auto& pair : componantMap) {
      std::cout << "Module: " << pair.first << "\n";
    }
  }
  
  


};


#endif
