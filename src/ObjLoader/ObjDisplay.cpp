#include "ObjDisplay.hpp"

#include <glm/gtc/type_ptr.hpp>

using glm::vec3;
auto OBJ::displayModel(const Model &model, float scale, bool colourFaces) -> void {
    glPushMatrix();
    glScalef(scale, scale, scale);
    for (const auto &face : model.Faces) {
        const auto hasMaterial = !model.Materials.empty();
        if (hasMaterial &&
            model.Materials[static_cast<size_t>(face.Material)].hasDiffuseTex) {
            glBindTexture(
                GL_TEXTURE_2D,
                model.Materials[static_cast<size_t>(face.Material)].diffuseTextureId);
        }

        glBegin(GL_POLYGON);
        if (colourFaces) {
            const auto &material =
                model.Materials[static_cast<size_t>(face.Material)];
            glColor3fv(glm::value_ptr(material.diffuse));
            glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT,
                         glm::value_ptr(material.ambient));
            glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR,
                         glm::value_ptr(material.specular));
            glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE,
                         glm::value_ptr(material.diffuse));
            glMaterialf(GL_FRONT_AND_BACK, GL_SHININESS, material.shininess);
        }
        for (size_t i = 0; i < face.Vertices.size(); i++) {
           /* auto &vertind     = face.Vertices[i];
            auto &uvind       = face.VertTexts[i];*/
            const auto &vert =
                model.Vertices[static_cast<size_t>(face.Vertices[i])];
            if (hasMaterial &&
                model.Materials[static_cast<size_t>(face.Material)].hasDiffuseTex) {
                const auto &uv = model.UVs[static_cast<size_t>(face.VertTexts[i])];
                glTexCoord2fv(glm::value_ptr(uv));
            }
            glVertex3f(vert.x, vert.y, vert.z);
        }
        glEnd();
    }
    glPopMatrix();
}

auto OBJ::displayModel(const Model &model, float scale) -> void {
    displayModel(model, scale, 1);
}
