#ifndef __COMPONENT_PARSER_CPP__
#define __COMPONENT_PARSER_CPP__

#include <json.hpp>
#include <iostream>
#include <string>
#include <vector>
#include <optional>

namespace ComponantParser {


using json = nlohmann::json;

struct Pin {
    std::string name;
};

// Simulation struct (logic and pins)
struct Simulation {
    std::optional<std::vector<Pin>> top;
    std::optional<std::vector<Pin>> bottom;
    std::optional<std::vector<Pin>> left;
    std::optional<std::vector<Pin>> right;
    std::string logic;
};


// Module struct (main container)
struct Module {
    std::string module;
    std::string description;
    std::optional<Simulation> logic_simulation;
    std::optional<Simulation> electrical_simulation;
};




// Pin parser
void from_json(const json& j, Pin& p) {
    j.at("name").get_to(p.name);
}



// Simulation parser
void from_json(const json& j, Simulation& s) {
    if (j.contains("pins")) {
        const json& pins = j.at("pins");

        if (pins.contains("top")) {
            s.top = pins.at("top").get<std::vector<Pin>>();
        }

        if (pins.contains("bottom")) {
            s.bottom = pins.at("bottom").get<std::vector<Pin>>();
        }

        if (pins.contains("left")) {
            s.left = pins.at("left").get<std::vector<Pin>>();
        }

        if (pins.contains("right")) {
            s.right = pins.at("right").get<std::vector<Pin>>();
        }
    }

    // logic is required
    if (!j.contains("logic"))
        throw std::runtime_error("Missing 'logic' field in simulation");
    s.logic = j.at("logic").get<std::string>();
}



// Module parser
void from_json(const json& j, Module& m) {
    j.at("module").get_to(m.module);
    j.at("description").get_to(m.description);

    if (j.contains("Logic_simulation"))
        m.logic_simulation = j.at("Logic_simulation").get<Simulation>();

    if (j.contains("Electrical_simulation"))
        m.electrical_simulation = j.at("Electrical_simulation").get<Simulation>();

    if (!m.logic_simulation && !m.electrical_simulation)
        throw std::runtime_error("At least one of Logic_simulation or Electrical_simulation must exist");
}


void log_pins(const std::string& label, const std::optional<std::vector<Pin>>& pins) {
    if (pins) {
        std::cout << "  " << label << " Pins:\n";
        for (const auto& pin : *pins) {
            std::cout << "    - " << pin.name << "\n";
        }
    }
}

void log_simulation(const std::string& sim_name, const std::optional<Simulation>& sim) {
    if (sim) {
        std::cout << sim_name << ":\n";
        log_pins("Top", sim->top);
        log_pins("Bottom", sim->bottom);
        log_pins("Left", sim->left);
        log_pins("Right", sim->right);
        std::cout << "  Logic:\n" << sim->logic << "\n";
    }
}

void log_componant(Module& m) {
    std::cout << "Module: " << m.module << "\n";
    std::cout << "Description: " << m.description << "\n";

    log_simulation("Logic Simulation", m.logic_simulation);
    log_simulation("Electrical Simulation", m.electrical_simulation);
}

}

#endif