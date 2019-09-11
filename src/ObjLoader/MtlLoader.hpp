#pragma once
#include <map>
#include <istream>

#include "Material.hpp"

class MTL {
public:
    auto static Load(const std::string & filepath) -> std::map<std::string, Material>;
};
