#include <map>
#include <string>
#include <vector>
#include <glm/gtc/type_ptr.hpp>
#include "../Stonk/OpenGl.hpp"
#include "ObjLoader.hpp"

class ModelManager {
public:
    static auto GetModelID(std::string filename) -> int {
        static std::map<std::string, size_t> nameToId = {};
        auto id = nameToId.find(filename);
        if (id != nameToId.end()) { // file not loaded yet
            ModelRepo().push_back(OBJ::Load(filename));
        } else {
            return id->second;
        }
    }
    static auto DrawModel(size_t id, const glm::vec3& scale, const glm::vec3& offset) -> void {
        glPushMatrix();
        glTranslatef(offset.x, offset.y, offset.z);
        // ModelDisplay::displayModel(ModelRepo()[id], scale, 1);
        throw "DrawModel( ... ) not implemented";
        glPopMatrix();
    }
    static auto DrawModel(size_t id, const glm::vec3& offset) -> void {
        DrawModel(id, {1,1,1}, offset);
    }
private:
    static auto ModelRepo() -> std::vector<Model> {
        static std::vector<Model> m = {};
        return m;
    }
};
