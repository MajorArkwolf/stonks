#pragma once
#include "Model.hpp"
#include <istream>

class OBJ {
public:
    auto static Load(std::istream& is) -> Model;
};
