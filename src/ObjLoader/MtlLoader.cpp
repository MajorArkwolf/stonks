#include "MtlLoader.hpp"

#include <string>
#include <sstream>
#include <fstream>

#include <stdexcept>

using std::string;

auto MTL::Load(const std::string & filepath) -> std::map<std::string, Material> {
    auto is = std::ifstream(filepath);
    string currentLine = "";
    string currentMaterial = "";
    std::map<std::string, Material> materials = {};
    while (std::getline(is >> std::ws, currentLine)) {
        
        auto line = std::stringstream(currentLine);
        string command = "";
        line >> command;

        if (command[0] == '#') {
            //comment, do nothing
        } 
        else if (command == "newmtl") {
            line >> currentMaterial;
        } 
        else if (command == "Ka") {   //ambient
            glm::vec3 Ka = {0, 0, 0};
            line >> Ka.r >> Ka.g >> Ka.b;
            materials[currentMaterial].ambient=Ka;
        } 
        else if (command == "Kd") {   //diffuse
            glm::vec3 Kd = {0, 0, 0};
            line >> Kd.r >> Kd.g >> Kd.b;
            materials[currentMaterial].diffuse=Kd;
        } 
        else if (command == "Ks") {   //specular
            glm::vec3 Ks = {0, 0, 0};
            line >> Ks.r >> Ks.g >> Ks.b;
            materials[currentMaterial].specular=Ks;
        }
        else if (command == "d") {     //non-transparency, opposite of Tr
            float d;
            line >> d;
            materials[currentMaterial].transparency = 1.0 - d;
        } 
        else if (command == "Tr") {   //transparency
            line >> materials[currentMaterial].transparency;
        } 
        else if (command == "Ns") {   //shininess
            line >> materials[currentMaterial].shininess;
        } 
        else if (command == "illum") {//illumination
            int mi;
            line >> mi;
            materials[currentMaterial].illumination = static_cast<Material::Illumination>(mi);
        } 
        else if (command == "map_Ka") {//texture map - ambient
            string filename = "";
            line >> filename;
            auto path  = string{} + "res/" + filename;
            // TODO: Load image
        }
    }
    return materials;  
}
