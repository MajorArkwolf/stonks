#pragma once
#include <map>
#include <istream>

#include "Material.hpp"

class MTL {
public:
    auto static Load(std::istream& is) -> std::map<std::string, Material>;
};
