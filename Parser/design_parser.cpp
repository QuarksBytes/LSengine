#ifndef __DESIGN_PARSER_CPP__
#define __DESIGN_PARSER_CPP__

#include <iostream>
#include <string>
#include <vector>
#include <optional>

#include "Json/json.hpp"
#include "Parser/component_parser.cpp"
namespace DesignParser {


    using json = nlohmann::json;


    // Pin inside a component
    struct DesignPin {
        std::string name;
        int id;
    };

    // Component in the design
    struct Component {
        std::string identity;
        std::string name;
        int id;
        std::vector<DesignPin> pins;
    };


    // Connection between two pin IDs
    struct Connection {
        int p0;
        int p1;
    };

    // Top-level Design
    struct Design {
        std::string name;
        std::string version;
        std::string description;
        std::vector<Component> components;
        std::vector<Connection> connections;
        std::vector<ComponentParser::Componant> dependantModules;
    };


    // DesignPin parser
    inline void from_json(const json& j, DesignPin& p) {
        j.at("name").get_to(p.name);
        j.at("id").get_to(p.id);
    }

    // Component parser
    inline void from_json(const json& j, Component& c) {
        j.at("identity").get_to(c.identity);
        j.at("name").get_to(c.name);
        j.at("id").get_to(c.id);
        j.at("pins").get_to(c.pins);
    }


    // Connection parser
    inline void from_json(const json& j, Connection& conn) {
        j.at("p0").get_to(conn.p0);
        j.at("p1").get_to(conn.p1);
    }

    // Design parser
    inline void from_json(const json& j, Design& d) {
        const auto& design = j.at("design");
        design.at("name").get_to(d.name);
        design.at("version").get_to(d.version);
        design.at("description").get_to(d.description);
        design.at("components").get_to(d.components);
        design.at("connections").get_to(d.connections);
        

         // Parse dependencies using ComponentParser::Componant
         if (design.contains("dependencies")) {
            design.at("dependencies").get_to(d.dependantModules);
        } else {
            d.dependantModules = std::vector<ComponentParser::Componant>();
        }
        
    }


    void log_design(const Design& d) {
        std::cout << "📐 Design: " << d.name << " (v" << d.version << ")\n";
        std::cout << "📝 Description: " << d.description << "\n\n";

        std::cout << "🔧 Components:\n";
        for (const auto& c : d.components) {
            std::cout << "  • [" << c.identity << "] " << c.name << " (ID: " << c.id << ")\n";
            for (const auto& pin : c.pins) {
                std::cout << "      ↳ Pin: " << pin.name << " (ID: " << pin.id << ")\n";
            }
        }

        std::cout << "\n🔌 Connections:\n";
        for (const auto& conn : d.connections) {
            std::cout << "  • Pin " << conn.p0 << " <--> Pin " << conn.p1 << "\n";
        }


        std::cout << "\n 📦 Dependant Modules:\n";
        for (const auto& m : d.dependantModules) {
            std::cout << "  • Module: " << m.module << "\n";
            std::cout << "    Description: " << m.description << "\n";
        }
        std::cout << "----------------------------------------\n";

    }
}

#endif
