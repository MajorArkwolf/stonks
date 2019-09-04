#pragma once

#include <glm/vec3.hpp>
#include <glm/vec2.hpp>
#include <vector>

#include "Material.hpp"

/**
 * @brief Model file
 */
struct Model {
    struct Face {
        std::vector<int> Vertices = {};
        std::vector<int> VertTexts = {};
    };

    // Model();
    /**
     * @brief Vertices
     */
    std::vector<glm::vec3> Vertices = {};
    /**
     * @brief Faces
     */
    std::vector<Face> Faces = {};
    /**
     * @brief UVs for the model
     */
    std::vector<glm::vec2> UVs = {};
    /**
     * @brief Materials used by the model
     */
    std::vector<Material> Materials = {};
};
