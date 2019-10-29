#pragma once

#include <vector>

#include <glm/vec2.hpp>
#include <glm/vec3.hpp>

#include "Material.hpp"

/**
 * @brief Model file
 */
struct Model {
    /**
     * @brief A face of the model
     */
    struct Face {
        /**
         * @brief The vertices that compose this face.
         * @sa Model.Vertices
         */
        std::vector<int> Vertices = {};
        /**
         * @brief The UV coordinates for each of the vertices.
         * @sa Model.UVs
         */
        std::vector<int> VertTexts = {};

		/**
         * @brief The UV coordinates for each of the Normals.
         * @sa Model.Norms
         */
		std::vector<int> VertNorms = {};
        /**
         * @brief The index for the material for this face.
         * @sa Model.Materials
         */
        int Material;
    };

    /**
     * @brief Vertices
     */
    std::vector<glm::vec3> Vertices = {};
    /**
     * @brief Vertices
     */
    std::vector<glm::vec3> Normals = {};
    /**
     * @brief Faces
     */
    std::vector<Face> Faces = {};
    /**
     * @brief UVs for the model
     */
    std::vector<glm::vec2> UVs = {};
    /**
     * @brief Materials used by the model.
     */
    std::vector<Material> Materials = {};
    /**
     * @brief Filename, for debugging
     */
    std::string Filename = "";
};
