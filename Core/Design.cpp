#ifndef _DESIGN_CPP
#define _DESIGN_CPP

#include"Componant.cpp"
#include<string>
#include<vector>

class Design
{
    public:
    std::string name;
    std::string description;
    std::vector<Componant> components;
    std::vector<Simulator> simulators;
};
#endif