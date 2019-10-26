#pragma once
#include <string>
#include <vector>

#include "Model.hpp"

class ModelManager {
  public:
    /**
     * @brief Gets a model for a filename, loading it if necessary. Keep the ID around
     */
    static auto GetModelID(std::string filename) -> size_t;
    /**
     * @brief Draw a model from its ID
     */
    static void DrawModel([[maybe_unused]] size_t id, GLfloat rotation,
                          [[maybe_unused]] const glm::vec3 &scale,
                          const glm::vec3 &offset);
    /**
     * @brief Draw a model from its ID
     */
    static auto DrawModel(size_t id, const glm::vec3 &offset) -> void;

  private:
    /**
     * @brief Stores all loaded models
     */
    static auto ModelRepo() -> std::vector<Model> &;
};
