#include <fstream>



#include"Core/engine.cpp"
#include"Modules/module_registry.cpp"


namespace fs = std::filesystem;

int main(){

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

    ModuleRegistry moduleRegistry(fileContents);

    auto& module=moduleRegistry.getModule("AND-gate");
    ComponentParser::log_component(module);




}
