#include "MtlLoader.hpp"

#include <fstream>
#include <sstream>
#include <stdexcept>
#include <string>

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

#include "Stonk/Engine.hpp"

using std::string;

auto MTL::GetImages() -> std::vector<Image>& {
    static std::vector<MTL::Image> Images = {};
    return Images;
};
auto MTL::GetTextures() -> std::vector<GLuint>& {
    static std::vector<GLuint> Textures = {};
    return Textures;
};
auto MTL::GetImagePaths() -> std::map<std::string, size_t>& {
    static std::map<std::string, size_t> ImageNames = {};
    return ImageNames;
};

auto MTL::Load(const std::string &filepath) -> std::map<std::string, Material> {
    auto &engine = Stonk::Engine::get();
    auto path              = engine.basepath + "res/model/" + filepath;
    auto is            = std::ifstream(path);
    string currentLine = "";
    string currentMaterial = "";
    // An MTL file can define multiple materials, which are stored by name here.
    std::map<std::string, Material> materials = {};
    while (std::getline(is >> std::ws, currentLine)) {

        auto line      = std::stringstream(currentLine);
        string command = "";
        line >> command;
        auto& material = materials[currentMaterial];

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
            auto &engine     = Stonk::Engine::get();
            auto texturePath = engine.basepath + "res/tex/" + filename;
            size_t index = 0;
            if (MTL::GetImagePaths().try_emplace(texturePath, index = MTL::GetImagePaths().size()).second) {
                //generate an openGL texture for this image
                GLuint boundTex;
                glGenTextures(1, &boundTex);
                glBindTexture(GL_TEXTURE_2D, boundTex);
                MTL::GetImages().push_back(Image{IMG_Load(texturePath.c_str()), &SDL_FreeSurface});

                const auto& image = MTL::GetImages()[index];
                glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
                glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST_MIPMAP_LINEAR);
                gluBuild2DMipmaps(GL_TEXTURE_2D, 3, image->w, image->h, GL_RGB,
                                GL_UNSIGNED_BYTE, image->pixels);
                MTL::GetTextures().push_back(boundTex);
            } else {
                index = MTL::GetImagePaths()[path];
            }
            if (command == "map_Ka") {
                material.ambientTextureId = MTL::GetTextures()[index];
                material.hasAmbientTex = true;
            } else if (command == "map_Kd") {
                material.diffuseTextureId = MTL::GetTextures()[index];
                material.hasDiffuseTex = true;
            }
        }
    }
    return materials;
}
