#pragma once
#include "glm/vec2.hpp"

namespace BSP {
    class Node {
      public:
        Node();
        Node(glm::vec2 bottomLeft, glm::vec2 topRight);
        ~Node();

        glm::vec2 getCentrePoint();

        Node *parent = nullptr;
        Node *left   = nullptr;
        Node *right  = nullptr;

        glm::vec2 gridTopRight   = {0, 0};
        glm::vec2 gridBottomLeft = {0, 0};
        int depth                = 0;
    };
};