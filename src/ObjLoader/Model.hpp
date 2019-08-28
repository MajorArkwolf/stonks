#include <vector>

#include <glm/vec3.hpp>

/**
 * @brief Model file
 */
struct Model {
    Model();
    /**
     * @brief Vertices
     */
    std::vector<glm::vec3> Vertices;
    /**
     * @brief Faces
     */
    std::vector<glm::vec3> Faces;
    /**
     * @brief Normals
     */
    std::vector<glm::vec3> Normals;
    /**
     * @brief Texture verts
     */
    std::vector<glm::vec2> TexVerts;
};
