#include <map>
#include <string>
#include <vector>
#include <glm/gtc/type_ptr.hpp>
#include "../Stonk/OpenGl.hpp"
#include "ObjLoader.hpp"

class ModelManager {
public:
    static auto GetModelID(std::string filename) -> size_t {
        static std::map<std::string, size_t> nameToId = {};
        auto id = nameToId.find(filename);
        if (id == nameToId.end()) { // file not loaded yet
            ModelRepo().push_back(OBJ::Load(filename));
            nameToId.emplace(filename, ModelRepo().size() - 1);
            return ModelRepo().size() - 1;
        } else {
            return id->second;
        }
    }
    static void DrawModel([[maybe_unused]] size_t id, GLfloat rotation,
                          [[maybe_unused]] const glm::vec3 &scale,
                          const glm::vec3 &offset) {
        glPushMatrix();
        glTranslatef(offset.x, offset.y, offset.z);
        glRotatef(rotation, 0, 1, 0);
        OBJ::displayModel(ModelRepo().at(id), scale, 1);
        //throw "DrawModel( ... ) not implemented";
        glPopMatrix();
    }
    static auto DrawModel(size_t id, const glm::vec3& offset) -> void {
        DrawModel(id, 0.0f ,{1,1,1}, offset);
        
    }
private:
    static auto ModelRepo() -> std::vector<Model>& {
        static std::vector<Model> m = {};
        return m;
    }
};
