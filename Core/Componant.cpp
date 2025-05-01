#ifndef _COMPONANT_CPP
#define _COMPONANT_CPP

#include"Parser/component_parser.cpp"

enum ComponantType{
    INPUT,
    PROCESS,
    OUTPUT
};

enum PinOrientation{
    LEFT,
    RIGHT,
    TOP,
    BOTTOM
};

class ComponantPin{
   public:
   std::string name;
   PinOrientation orientation;
   ComponantPin(std::string name, PinOrientation orientation) : name(name), orientation(orientation) {}
};

class Simulator{
    public:
    std::vector<ComponantPin> pins;
    std::string logic;

    Simulator(Parser::Simulation& simulation)
    {
           for(auto& pin : simulation.top.value())
               pins.push_back(ComponantPin(pin.name, TOP));
           
           for(auto& pin : simulation.bottom.value())
               pins.push_back(ComponantPin(pin.name, BOTTOM));    

           for(auto& pin : simulation.left.value())
               pins.push_back(ComponantPin(pin.name, LEFT)); 
               
           for(auto& pin : simulation.right.value())
               pins.push_back(ComponantPin(pin.name, RIGHT)); 
               
           logic = simulation.logic;    

    }
};



class Componant
{
    public:
    std::string moduleName;
    std::string moduleDescription;
    uint16_t width;
    uint16_t height;
    ComponantType type;
    
    Simulator& logicSimulator;
    Simulator& electricalSimulator;

    Componant(Parser::ComponantParsed& parsedComponant): logicSimulator(*new Simulator(parsedComponant.logic_simulation.value())),
                                                         electricalSimulator(*new Simulator(parsedComponant.electrical_simulation.value()))
    {
        moduleName = parsedComponant.module;
        moduleDescription = parsedComponant.description;
        width = parsedComponant.width;
        height = parsedComponant.height;
         //setting up the type of the module
        if(parsedComponant.type == "input")
            type = INPUT;
        else if(parsedComponant.type == "process")
            type = PROCESS;
        else if(parsedComponant.type == "output")
            type = OUTPUT;
        else
            throw std::runtime_error("Unknown module type: " + parsedComponant.type);
    }

};

#endif