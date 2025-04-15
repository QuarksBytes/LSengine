#include <iostream>
#include <fstream>
#include <string>
#include <filesystem>
#include <vector>
#include <module_registry.cpp>

namespace fs = std::filesystem;

int main() {
    std::string directory = "sampleComponants";
    std::vector<std::string> fileContents;
   
    //read file from directory
    try {
        for (const auto& entry : fs::directory_iterator(directory)) {
            if (entry.is_regular_file()) {
                std::ifstream file(entry.path());
                if (file.is_open()) {
                    std::string content((std::istreambuf_iterator<char>(file)), std::istreambuf_iterator<char>());
                    fileContents.push_back(content);
                    file.close();
                } else {
                    std::cerr << "Failed to open file: " << entry.path() << "\n";
                }
            }
        }
    } catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << "\n";
        return 1;
    }


    try{
          
        ModuleRegistry moduleRegistry(fileContents);


        ComponantParser::Module& module = moduleRegistry.getModule("AND-gate");
        ComponantParser::log_componant(module);
    }
    catch(const std::exception& e){
        std::cerr << "Error parsing JSON: " << e.what() << "\n";
        return 1;
    }



    

    return 0;
}