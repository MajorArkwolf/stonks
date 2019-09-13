#include "ObjLoader.hpp"
#include <glm/vec3.hpp>
#include <glm/vec2.hpp>
#include <string>
#include <sstream>
#include <iostream>
#include <fstream>

#include "MtlLoader.hpp"

using std::string;

auto OBJ::Load(const std::string & filepath) -> Model {
    auto is = std::ifstream(filepath);
    string currentLine = "";
    string groupName = "";
    string currentMaterial = "";
    Model mdl = {};
    //Materials currently loaded by the model
    std::map<string, Material> mats = {};
    //Maps a material to an integer ID, for use in the model.
    std::map<string, int> materialMapping = {};
    while (std::getline(is >> std::ws, currentLine)) {
        
        auto ss = std::stringstream(currentLine);
        string command = "";
        ss >> command;
        if (command[0] == '#') {
            //comment, do nothing
        } 
        else if (command == "v") //vertex
        {
            glm::vec3 v = {0,0,0};
            ss >> v.x >> v.y >> v.z;
            mdl.Vertices.push_back(v);
        } 
        else if (command == "vn") //normals
        {
            // glm::vec3 n = {0, 0, 0};
            // ss >> n.x >> n.y >> n.z;
            // mdl.Normals.push_back(n);
        } 
        else if (command == "vt") //texture
        {
            glm::vec2 tex = {0,0};
            ss >> tex.x >> tex.y;
            mdl.UVs.push_back(tex);
        } 
        else if (command == "g") // group name
        {
            //Not useful, IIRC
        } 
        else if (command == "f") {// faces 
            Model::Face f{};
            f.Material = materialMapping[currentMaterial];
            while (!(ss >> std::ws).eof()) {
                string faceVert = "";
                ss >> faceVert;
                std::stringstream faceVertRead(faceVert);
                // vertex
                string vStr = "";
                // vertex texture (UV)
                string vtStr = "";
                // vertex normal
                string vnStr = "";
                std::getline(faceVertRead, vStr, '/');
                std::getline(faceVertRead, vtStr, '/');
                std::getline(faceVertRead, vnStr);
                int v = 0, vt = 0, vn = 0;
                std::stringstream(vStr) >> v;
                std::stringstream(vtStr) >> vt;
                std::stringstream(vnStr) >> vn;
                f.Vertices.push_back(v - 1);
                f.VertTexts.push_back(vt - 1);
                // f.VertNorms.push_back(vn);
            }
            mdl.Faces.push_back(f);
        } 
        else if (command == "mtllib") {
            string mtlName = "";
            //Because of filenames being able to have spaces
            //We need to get the whole line
            std::getline(ss >> std::ws, mtlName);
            if (mtlName[mtlName.size() - 1] == '\r') {
                //Thanks to the C++ spec, reading a line on linux
                //will keep around carriage returns, if the file
                //is using windows-style line endings.
                mtlName = mtlName.substr(0, mtlName.size() - 1);
            }
            mats = MTL::Load(mtlName);    
        } 
        else if (command == "usemtl") {
            ss >> currentMaterial;
            if (materialMapping.try_emplace(currentMaterial, mdl.Materials.size()).second) {
                mdl.Materials.push_back(mats[currentMaterial]);
            }
        } 
        else if (command == "o") {
            //do nothing - o command does nothing
            /* (From spec:)
                Optional statement; it is not processed by any Wavefront programs.
                It specifies a user-defined object name for the elements defined
                after this statement.
            */
        } 
        else if (command == "s") {
            //Specify a bitmask of which smoothing groups the following vertices are a part of
            //Not yet implemented
            //TODO: Implement
        } 
        else {
            // std::cout << "Unrecognized OBJ command found: " << currentLine << std::endl;
        }
        
        
    }
    return mdl;
}
