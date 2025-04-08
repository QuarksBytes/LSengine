#include <iostream>
#include <fstream>
#include "json.hpp"  // assuming json.hpp is in the same directory or included properly

using json = nlohmann::json;

int main() {
    std::ifstream file("test.json");

    if (!file) {
        std::cerr << "Failed to open data.json" << std::endl;
        return 1;
    }

    json j;
    file >> j;  // Read and parse the JSON file

    std::cout << "Name: " << j["name"] << std::endl;
    std::cout << "Age: " << j["age"] << std::endl;

    std::cout << "Skills: ";
    for (const auto& skill : j["skills"]) {
        std::cout << skill << " ";
    }
    std::cout << std::endl;

    return 0;
}
