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
    auto GetAmbient() -> const glm::vec3& {
        return this->ambient;
    }
    auto GetDiffuse() -> const glm::vec3& {
        return this->diffuse;
    }
    auto GetSpecular() -> const glm::vec3&  {
        return this->specular;
    }
    auto GetTransparency() -> float {
        return this->transparency;
    }
    auto GetShininess() -> float {
        return this->shininess;
    }
    auto GetIllumination() -> Illumination {
        return this->illumination;
    } 
    auto SetAmbient(const glm::vec3& Ka) -> void {
        this->ambient = Ka;
    }
    auto SetDiffuse(const glm::vec3& Kd) -> void {
        this->diffuse = Kd;
    }
    auto SetSpecular(const glm::vec3& Ks) -> void {
        this->specular = Ks;
    }
    auto SetTransparency(float t) -> void {
        this->transparency = t;
    }
    auto SetShininess(float s) -> void {
        this->shininess = s;
    }
    auto SetIllumination(Illumination i) -> void {
        this->illumination = i;
    } 
private:
    //Uses default values provided from https://people.sc.fsu.edu/~jburkardt/data/mtl/mtl.html
    glm::vec3 ambient = {0.2, 0.2, 0.2};
    glm::vec3 diffuse = {0.8, 0.8, 0.8};
    glm::vec3 specular = {1.0, 1.0, 1.0};
    float transparency = 0.0;
    float shininess = 0.0;
    //No default value provided in spec, assuming Flat
    Illumination illumination = Illumination::Flat;
};
