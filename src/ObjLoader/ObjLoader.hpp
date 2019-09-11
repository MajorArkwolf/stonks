#pragma once
#include "Model.hpp"
#include <istream>

namespace OBJ {
    
    /**
     * Loads an OBJ model. Does not have full support for the OBJ standard, but
     * supports a majority of the actually used Obj commands.
     * @brief Loads an OBJ model
     * @param filepath The path of the OBJ file to load
     * @return The model itsself
     */
    auto static Load(const std::string & filepath) -> Model;
};
