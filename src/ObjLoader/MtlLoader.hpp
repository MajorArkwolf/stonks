#pragma once
#include <map>
#include <istream>

#include "Material.hpp"

namespace MTL {

    /**
     * Loads a material file, so long as it mostly adheres to the standard.
     * @brief Load an MTL material file
     * @param filepath The path of the material file to load
     * @return A mapping of material names to material data.
     */
    auto static Load(const std::string & filepath) -> std::map<std::string, Material>;
};
