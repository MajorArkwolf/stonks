#include "ObjLoader.hpp"
#include <glm/vec3.hpp>
#include <glm/vec2.hpp>
#include <string>
#include <sstream>
#include <iostream>
#include <fstream>

#include "MtlLoader.hpp"

using std::string;

auto OBJ::Load(std::istream& is) -> Model {
    string currentLine = "";
    string groupName = "";
    string currentMaterial;
    Model m = {};
    std::map<string, Material> mats = {};
    //Maps a material to an integer ID, for use in the model.
    std::map<string, int> materialMapping = {};
    while (std::getline(is >> std::ws, currentLine)) {
        // std::cout << "OBJ: " << currentLine << std::endl;
        auto ss = std::stringstream(currentLine);
        string command = "";
        ss >> command;
        if (command[0] == '#') {
            //comment, do nothing
        } else if (command == "v") //vertex
        {
            glm::vec3 v = {0,0,0};
            ss >> v.x >> v.y >> v.z;
            m.Vertices.push_back(v);
        } else if (command == "vn") //normal
        {
            // float i, j, k; //names from OBJ.spec
            // ss >> i >> j >> k;
            // glm::vec3 n = {i, j, k};
            // m.Normals.push_back(n);
        } else if (command == "vt") //texture
        {
            glm::vec2 tex = {0,0};
            ss >> tex.x >> tex.y;
            m.UVs.push_back(tex);
        } else if (command == "g") // group name
        {
            groupName = ""; //reset to blank group name
            ss >> groupName;
        } else if (command == "f") {// faces 
            Model::Face f{};
            f.Material = materialMapping[currentMaterial];
            while (!(ss >> std::ws).eof()) {
                string faceVert = "";
                ss >> faceVert;
                std::stringstream faceVertRead(faceVert);
                string vStr = "";
                string vtStr = "";
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
            m.Faces.push_back(f);
        } else if (command == "mtllib") {
            string mtlName = "";
            std::getline(ss >> std::ws, mtlName);
            if (mtlName[mtlName.size() - 1] == '\r') {
                mtlName = mtlName.substr(0, mtlName.size() - 1);
            }
            std::ifstream ifile(mtlName);
            mats = MTL::Load(ifile);    
        } else if (command == "usemtl") {
            ss >> currentMaterial;
            if (materialMapping.try_emplace(currentMaterial, m.Materials.size()).second) {
                m.Materials.push_back(mats[currentMaterial]);
            }
        } else if (command == "o") {
            //do nothing - o command does nothing
            /* (From spec:)
                Optional statement; it is not processed by any Wavefront programs.
                It specifies a user-defined object name for the elements defined
                after this statement.
            */
        } else if (command == "s") {
            //smoothing groups, currently unimplemented
            //todo: implement
        } else {
            std::cout << "Unrecognized OBJ command found: " << currentLine << std::endl;
        }
        
        
    }
    return m;
}
