#pragma once
#include <string>
#include "Model.hpp"
#include <vector>

class ModelManager {
public:
    static auto GetModelID(std::string filename) -> size_t;
    static void DrawModel([[maybe_unused]] size_t id, GLfloat rotation,
                          [[maybe_unused]] const glm::vec3 &scale,
                          const glm::vec3 &offset);
    static auto DrawModel(size_t id, const glm::vec3& offset) -> void;
private:
    static auto ModelRepo() -> std::vector<Model>&;
};
