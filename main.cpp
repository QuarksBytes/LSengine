
#include "Parser/design_parser.cpp"
#include <fstream>
#include <iostream>

int main(int argc, char* argv[]){
    std::ifstream file("Parser/sample_design_format.json");
    if (!file.is_open()) {
        std::cerr << "Failed to open file\n";
        return 1;
    }

    try {
        Parser::json j;
        file >> j;

        Parser::DesignParsed d = j.get<Parser::DesignParsed>();
        Parser::log_design(d);


    } catch (const std::exception& e) {
        std::cerr << "Error parsing JSON: " << e.what() << "\n";
        return 1;
    }

    
    return 0;
}
