#include "MtlLoader.hpp"

#include <string>
#include <sstream>

#include <iostream>

#include <stdexcept>

using std::string;

auto MTL::Load(std::istream& is) -> std::map<std::string, Material> {
    string currentLine = "";
    string currentMaterial = "";
    std::map<std::string, Material> materials = {};
    while (std::getline(is >> std::ws, currentLine)) {
        
        auto line = std::stringstream(currentLine);
        string command = "";
        line >> command;

        if (command[0] == '#') {
            //comment, do nothing
        } else if (command == "newmtl") {
            line >> currentMaterial;
        } else if (command == "Ka") {   //ambient
            float R, G, B;
            line >> R >> G >> B;
            glm::vec3 Ka = {R, G, B};
            materials[currentMaterial].ambient = Ka;
        } else if (command == "Kd") {   //diffuse
            float R, G, B;
            line >> R >> G >> B;
            glm::vec3 Kd = {R, G, B};
            materials[currentMaterial].diffuse=Kd;
        } else if (command == "Ks") {   //specular
            float R, G, B;
            line >> R >> G >> B;
            glm::vec3 Ks = {R, G, B};
            materials[currentMaterial].specular=Ks;
        }else if (command == "d") {     //non-transparency, opposite of Tr
            float d;
            line >> d;
            materials[currentMaterial].transparency=1.0 - d;
        } else if (command == "Tr") {   //transparency
            float t;
            line >> t;
            materials[currentMaterial].transparency = t;
        } else if (command == "Ns") {   //shininess
            float ns;
            line >> ns;
            materials[currentMaterial].shininess = ns;
        } else if (command == "illum") {//illumination
            int mi;
            line >> mi;
            materials[currentMaterial].illumination = static_cast<Material::Illumination>(mi);
        } else if (command == "map_Ka") {
            string filename = "";
            line >> filename;
            auto path  = string{} + "res/" + filename;
            // TODO: Load image
        }
    }
    return materials;  
}
