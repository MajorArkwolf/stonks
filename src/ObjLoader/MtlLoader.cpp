#include "MtlLoader.hpp"

#include <fstream>
#include <sstream>
#include <stdexcept>
#include <string>

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

using std::string;
std::vector<MTL::Image> MTL::Images = {};
std::vector<GLuint> MTL::Textures = {};
std::map<std::string, int> MTL::ImageNames = {};

auto MTL::Load(const std::string &filepath) -> std::map<std::string, Material> {
    auto path          = string{SDL_GetBasePath()} + "res/model/" + filepath;
    auto is            = std::ifstream(path);
    string currentLine = "";
    string currentMaterial = "";
    // An MTL file can define multiple materials, which are stored by name here.
    std::map<std::string, Material> materials = {};
    while (std::getline(is >> std::ws, currentLine)) {

        auto line      = std::stringstream(currentLine);
        string command = "";
        line >> command;

        if (command[0] == '#') {
            // comment, do nothing
        } else if (command == "newmtl") {
            line >> currentMaterial;
        } else if (command == "Ka") { // ambient
            glm::vec3 Ka = {0, 0, 0};
            line >> Ka.r >> Ka.g >> Ka.b;
            materials[currentMaterial].ambient = Ka;
        } else if (command == "Kd") { // diffuse
            glm::vec3 Kd = {0, 0, 0};
            line >> Kd.r >> Kd.g >> Kd.b;
            materials[currentMaterial].diffuse = Kd;
        } else if (command == "Ks") { // specular
            glm::vec3 Ks = {0, 0, 0};
            line >> Ks.r >> Ks.g >> Ks.b;
            materials[currentMaterial].specular = Ks;
        } else if (command == "d") { // non-transparency, opposite of Tr
            float d;
            line >> d;
            materials[currentMaterial].transparency = 1.0f - d;
        } else if (command == "Tr") { // transparency
            line >> materials[currentMaterial].transparency;
        } else if (command == "Ns") { // shininess
            line >> materials[currentMaterial].shininess;
        } else if (command == "illum") { // illumination
            int mi;
            line >> mi;
            materials[currentMaterial].illumination =
                static_cast<Material::Illumination>(mi);
        } else if (command == "map_Ka" || command == "map_Kd") { // texture maps
            string filename = "";
            line >> filename;
            //  TODO: This leaks memory (just like almost every use of SDL_GetBasePath in this codebase)
            auto texturePath  = string{SDL_GetBasePath()} + "res/model/" + filename;
            int id = 0;
            if (ImageNames.try_emplace(texturePath, id = ImageNames.size()).second) {
                GLuint boundTex;
                glGenTextures(1, &boundTex);
                glBindTexture(GL_TEXTURE_2D, boundTex);
                Images.push_back(Image{IMG_Load(texturePath.c_str()), &SDL_FreeSurface});
                const int level_of_detail = 0, border_width = 0;
                const auto& img = Images[id];
                const auto bpp = img->format->BytesPerPixel;
                const auto image_format = bpp == 4 ? GL_UNSIGNED_INT
                                        : bpp == 2 ? GL_UNSIGNED_SHORT
                                        : GL_UNSIGNED_BYTE;
                const auto image_format = GL_UNSIGNED_BYTE;
                glTexImage2D(GL_TEXTURE_2D, level_of_detail, GL_RGB, img->w, img->h, border_width, GL_RGB, image_format, img->pixels);
                Textures.push_back(boundTex);
            } else {
                id = MTL::ImageNames[path];
            }
            if (command == "map_Ka") {
                materials[currentMaterial].ambientTextureId = id;
            } else if (command == "map_Kd") {
                materials[currentMaterial].diffuseTextureId = id;
            }
        }
    }
    return materials;
}
