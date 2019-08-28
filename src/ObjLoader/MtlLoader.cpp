#include "MtlLoader.hpp"

#include <string>
#include <sstream>

#include <stdexcept>

using std::string;

auto MTL::Load(std::istream& is) -> std::map<std::string, Material> {
    string currentLine = "";
    string currentMaterial = "";
    std::map<std::string, Material> materials = {};
    while (!std::getline(is, currentLine).eof()) {
        auto ss = std::stringstream(currentLine);
        string command = "";
        ss >> command;
        if (command[0] == '#') {
            //comment
            break;
        } else if (command == "newmtl") {
            ss >> currentMaterial;
        } else if (command == "Ka") {
            float R, G, B;
            ss >> R, G, B;
            glm::vec3 Ka = {R, G, B};
            materials[currentMaterial].SetAmbient(Ka);
        } else if (command == "Kd") {
            float R, G, B;
            ss >> R, G, B;
            glm::vec3 Kd = {R, G, B};
            materials[currentMaterial].SetDiffuse(Kd);
        } else if (command == "Ks") {
            float R, G, B;
            ss >> R, G, B;
            glm::vec3 Ks = {R, G, B};
            materials[currentMaterial].SetSpecular(Ks);
        }else if (command == "d") {   
            //non-transparency, opposite of Tr
            float d;
            ss >> d;
            materials[currentMaterial].SetTransparency(1.0 - d);
        } else if (command == "Tr") {
            float t;
            ss >> t;
            materials[currentMaterial].SetTransparency(t);
        } else if (command == "Ns") {
            float ns;
            ss >> ns;
            materials[currentMaterial].SetShininess(ns);
        } else if (command == "illum") {
            int mi;
            ss >> mi;
            materials[currentMaterial].SetIllumination(static_cast<Material::Illumination>(mi));
        } else if (command == "map_Ka") {
            throw std::logic_error("not yet implemented. :(");
        }
    }  
    return materials;  
}
