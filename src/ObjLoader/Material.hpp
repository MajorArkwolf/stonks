#pragma once

#include <glm/vec3.hpp>
/**
 * @brief Defines a Material for rendering.
 */
class Material {
public:
    enum class Illumination {
        Flat = 1,
        Specular = 2
    };
    //Uses default values provided from https://people.sc.fsu.edu/~jburkardt/data/mtl/mtl.html
    glm::vec3 ambient = {0.2, 0.2, 0.2};
    glm::vec3 diffuse = {0.8, 0.8, 0.8};
    glm::vec3 specular = {1.0, 1.0, 1.0};
    float transparency = 0.0;
    float shininess = 0.0;
    //No default value provided in spec, assuming Flat
    Illumination illumination = Illumination::Flat;
};
