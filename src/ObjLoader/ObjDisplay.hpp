#pragma once
#include "ObjLoader.hpp"

namespace OBJ {
     auto displayModel(const Model &model, float scale, bool colourFaces)
        -> void;
     auto displayModel(const Model &model, float scale) -> void;
};