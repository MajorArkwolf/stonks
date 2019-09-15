#pragma once

#include <glm/vec3.hpp>
/**
 * Material data for OBJ files.
 * Default values from https://people.sc.fsu.edu/~jburkardt/data/mtl/mtl.html.
 * @brief Defines a Material for rendering.
 */
class Material {
  public:
    /**
     * @brief Illumination used by this model
     */
    enum class Illumination { Flat = 1, Specular = 2 };
    /**
     * @brief Ambient colour
     */
    glm::vec3 ambient = {0.2, 0.2, 0.2};
    /**
     * @brief Diffuse colour
     */
    glm::vec3 diffuse = {0.8, 0.8, 0.8};
    /**
     * @brief Specular colour
     */
    glm::vec3 specular = {1.0, 1.0, 1.0};
    /**
     * @brief Transparency
     */
    float transparency = 0.0;
    /**
     * @brief Shininess
     */
    float shininess = 0.0;
    /**
     * Illumination model used by the material. No default value
     * is provided in the spec, so I've assumed Flat as the default.
     * @brief The illumination model for this material.
     *
     */
    Illumination illumination = Illumination::Flat;
};
