#ifndef _DESIGN_CPP
#define _DESIGN_CPP

#include"Parser/design_parser.cpp"
#include"Componant.cpp"
#include "Modules/Componants_registry.cpp"
#include<string>
#include<vector>

struct PinComponant{
    std::string name;
    int id;
    Componant* parentComponant;
};


class Design
{
    public:
    std::string name;
    std::string description;
    std::string version;
    std::map<int, Componant> components; 
    std::map<int, PinComponant> pins; 
    std::vector<std::pair<int,int>> connections; 

    Design(Parser::DesignParsed designParsed, ComponantRegistry& registry) {
        // Setting up the design
        name = designParsed.name;
        description = designParsed.description;
        version = designParsed.version;
        

         // Adding dependent modules to the registry
        for (auto& module : designParsed.dependantModules) {
            registry.addComponant(module); // Add to the registry
        }   

        // Adding reference components to the design
        for (auto& component : designParsed.components) {
            Parser::ComponantParsed parsedComponant = registry.getComponant(component.identity);
            components[component.id] = Componant(parsedComponant); // Use component.id as the key
        }


        // Adding PinComponant to the design
      for (auto& component : designParsed.components) {
        // Ensure the component exists in the components map
       if (components.find(component.id) != components.end()) {
        for (auto& pin : component.pins) {
            pins[pin.id] = PinComponant{pin.name, pin.id, &components[component.id]};
        }
       } else {
        throw std::runtime_error("Component with ID " + std::to_string(component.id) + " not found in components map.");
         }
       }


        // Adding connections to the design
        for (auto& connection : designParsed.connections) {
            connections.push_back(std::make_pair(connection.p0, connection.p1));
        }



    }  


    uint32_t addComponant(Componant& m){
        components[components.size()] = m;
        return components.size();
    }



   
};
#endif