
#include "Parser/componant_parser.cpp"
#include <fstream>
#include <iostream>

int main(int argc, char* argv[]){
    std::ifstream file("Parser/sample_componant_format.json");
    if (!file.is_open()) {
        std::cerr << "Failed to open file\n";
        return 1;
    }

    try {
        json j;
        file >> j;

        Module module = j.get<Module>();

       log_componant(module);

    } catch (const std::exception& e) {
        std::cerr << "Error parsing JSON: " << e.what() << "\n";
        return 1;
    }

    
    return 0;
}