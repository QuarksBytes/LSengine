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

        // Assuming you have a Design object to pass to the Engine constructor
        //printing the modules in the registry
        for(auto& module : moduleRegistry.moduleMap){
            std::cout << "Module: " << module.first << "\n";
            std::cout << "Description: " << module.second.description << "\n";
            std::cout << "Width: " << module.second.width << "\n";
            std::cout << "Height: " << module.second.height << "\n";
            std::cout << "Type: " << module.second.type << "\n\n";
        }
    }
    catch(const std::exception& e){
        std::cerr << "Error parsing JSON: " << e.what() << "\n";
        return 1;
    }
    

    return 0;
}