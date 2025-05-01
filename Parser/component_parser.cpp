#ifndef __COMPONENT_PARSER_CPP__
#define __COMPONENT_PARSER_CPP__

#include "Json/json.hpp"
#include <iostream>
#include <string>
#include <vector>
#include <optional>

namespace Parser {

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
    std::string functionName;  // add name of function when parsing
    std::string logic;
  };


  // Module struct (main container)
  struct ComponantParsed {
    std::string module;
    std::string description;
    std::optional<Simulation> logic_simulation;
    std::optional<Simulation> electrical_simulation;
    std::string type;
    uint32_t width;
    uint32_t height;
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

    if (j.contains("functionName")) {
      s.functionName = j.at("functionName").get<std::string>();
  }
  

    // logic is required
    if (!j.contains("logic"))
      throw std::runtime_error("Missing 'logic' field in simulation");
    s.logic = j.at("logic").get<std::string>();
  }



  // Module parser
  void from_json(const json& j, ComponantParsed& m) {
    j.at("module").get_to(m.module);
    j.at("description").get_to(m.description);
    j.at("width").get_to(m.width);
    j.at("height").get_to(m.height);
    std::string type;
    j.at("type").get_to(type); 

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

  void log_component(ComponantParsed& m) {
    std::cout << "Module: " << m.module << "\n";
    std::cout << "width: " << m.width << "\n";
    std::cout << "height: " << m.height << "\n";
    std::cout << "Type: " << m.type << "\n";
    std::cout << "Description: " << m.description << "\n";

    log_simulation("Logic Simulation", m.logic_simulation);
    log_simulation("Electrical Simulation", m.electrical_simulation);
  }

}

#endif
