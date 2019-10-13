#pragma once
#include <istream>
#include <map>
#include <memory>
#include <vector>
#include <SDL2/SDL_image.h>
#include "Material.hpp"
#include "../Stonk/OpenGl.hpp"

class MTL {
public:
    /**
     * Loads a material file, so long as it mostly adheres to the standard.
     * @brief Load an MTL material file
     * @param filepath The path of the material file to load
     * @return A mapping of material names to material data.
     */
    static auto Load(const std::string &filepath) -> std::map<std::string, Material>;

    // Stolen from TexturedPolygons.hpp
    using Image = std::unique_ptr<SDL_Surface, decltype(&SDL_FreeSurface)>;

    /**
     * Stores images.
     */
    static auto GetImages() -> std::vector<Image>&;
    /**
     * Stores textures (OpenGL bound)
     */
    static auto GetTextures() -> std::vector<GLuint>&;
    /**
     * Image paths tell you where in the Images vector you can find an image.
     * This prevents the same image file from being loaded multiple times.
     */
    static auto GetImagePaths() -> std::map<std::string, size_t>&;
};
