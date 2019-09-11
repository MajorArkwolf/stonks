#pragma once
#include "Model.hpp"
#include <istream>

class OBJ {
public:
    auto static Load(const std::string & filepath) -> Model;
};
