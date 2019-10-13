#include "BSP.hpp"

#include <cmath>
#include <iostream>
#include <random>

#include <glm/vec2.hpp>

using BSP::Node;

BSP::BSPTree::BSPTree(glm::vec2 size, int subdivisions) {
    glm::vec2 bottomLeft = {1, 1};
    glm::vec2 topRight   = {size.x, size.y};
    root                 = new Node(bottomLeft, topRight);

    populateTree(root, subdivisions);
    splitNode(root);
    traverse(root);
}

BSP::BSPTree::BSPTree() {
    root = nullptr;
}

BSP::BSPTree::~BSPTree() {
    delete (root);
    root = nullptr;
}

const BSP::BSPTree &BSP::BSPTree::operator=(const BSPTree &rhs) {
    if (this != &rhs) {
        if (root != nullptr) {
            delete (root);
        }
        if (rhs.root == nullptr) {
             root == nullptr;
        } else {
            copyTree(root, rhs.root);
        }
    }

    return *this;
}

void BSP::BSPTree::deleteTree() {
    delete (root);
    root = nullptr;
}

void BSP::BSPTree::reGen(glm::vec2 size, int subdivisions) {
    deleteTree();

    glm::vec2 bottomLeft = {0, 0};
    glm::vec2 topRight   = {size.x, size.y};
    root                 = new Node(bottomLeft, topRight);

    populateTree(root, subdivisions);
    splitNode(root);
    traverse(root);
}

void BSP::BSPTree::populateTree(BSP::Node *node, int subdivisions) {
    if (node->depth < subdivisions) {

        if (node->left == nullptr) {
            node->left         = new BSP::Node();
            node->left->depth  = node->depth + 1;
            node->left->parent = node;
        }
        if (node->right == nullptr) {
            node->right         = new BSP::Node();
            node->right->depth  = node->depth + 1;
            node->right->parent = node;
        }

        splitNode(node);

        if (node->left != nullptr) {
            populateTree(node->left, subdivisions);
        }
        if (node->right != nullptr) {
            populateTree(node->right, subdivisions);
        }
    }
}

std::vector<Node *> BSP::BSPTree::getRooms() {
    std::vector<Node *> roomList;

    traverse(root, roomList);

    return roomList;
}

bool BSP::BSPTree::splitNode(BSP::Node *node) {

    bool vertical = 1;
    unsigned cutoffRange =
        30; // Needs to be between 10 and 40 for best results, higher = more random room sizes

    std::random_device dev;
    std::mt19937 rng(dev());
    std::uniform_int_distribution<std::mt19937::result_type> dist(1, 100);

    auto parentSize = node->gridTopRight - node->gridBottomLeft;

    if ((parentSize.x / parentSize.y) < 1.5f) {
        vertical = 0;
    }
    /*if (dist(rng) > 50) {
        vertical = 0;
    }*/

    std::uniform_int_distribution<std::mt19937::result_type> dist35(
        50 - cutoffRange, 50 + cutoffRange);

    glm::vec2 nodeSize = node->gridTopRight - node->gridBottomLeft;

    float cutoff = static_cast<float>(dist35(rng)) / 100;

    if (vertical) {
        glm::vec2 topRight = {
            std::round(cutoff * nodeSize.x + node->gridBottomLeft.x),
            std::round(node->gridTopRight.y)};
        glm::vec2 bottomLeft = {std::round(topRight.x + 1),
                                std::round(node->gridBottomLeft.y)};

        node->left->gridBottomLeft  = node->gridBottomLeft;
        node->left->gridTopRight    = topRight;
        node->right->gridBottomLeft = bottomLeft;
        node->right->gridTopRight   = node->gridTopRight;
    } else {
        glm::vec2 topRight = {
            std::round(node->gridTopRight.x),
            std::round(cutoff * nodeSize.y + node->gridBottomLeft.y)};
        glm::vec2 bottomLeft = {std::round(node->gridBottomLeft.x),
                                std::round(topRight.y + 1)};

        node->left->gridBottomLeft  = node->gridBottomLeft;
        node->left->gridTopRight    = topRight;
        node->right->gridBottomLeft = bottomLeft;
        node->right->gridTopRight   = node->gridTopRight;
    }
    return 0;
}

int BSP::BSPTree::traverse(BSP::Node *node, std::vector<Node *> &list) {

    if (node == nullptr) {
        return 0;
    }

    if (node->left == nullptr && node->right == nullptr) {
        list.push_back(node);
    }

    if (node->left != nullptr) {
        traverse(node->left, list);
    }

    if (node->right != nullptr) {
        traverse(node->right, list);
    }

    return 0;
}

void BSP::BSPTree::copyTree(Node *&copiedTreeRoot, Node *otherTreeRoot) {
    if(otherTreeRoot == nullptr) copiedTreeRoot = nullptr;
    else {
        copiedTreeRoot       = new Node;
        copiedTreeRoot->gridBottomLeft = otherTreeRoot->gridBottomLeft;
        copiedTreeRoot->gridTopRight = otherTreeRoot->gridTopRight;
        copiedTreeRoot->depth = otherTreeRoot->depth;
        copyTree(copiedTreeRoot->left, otherTreeRoot->left);
        copyTree(copiedTreeRoot->right, otherTreeRoot->right);
    }
}

int BSP::BSPTree::traverse(BSP::Node *node) {

    if (node == nullptr) {
        return 0;
    }
    /*if (node->depth == 3) {

        std::cout << "Node info: " << std::endl
                  << "Depth: " << node->depth << std::endl
                  << "Bottom left grid space : " << node->gridBottomLeft.x
                  << ", " << node->gridBottomLeft.y << std::endl
                  << "Top right grid space : " << node->gridTopRight.x << ", "
                  << node->gridTopRight.y << std::endl
                  << std::endl;
    }*/

    if (node->left != nullptr) {
        traverse(node->left);
    }

    if (node->right != nullptr) {
        traverse(node->right);
    }

    return 0;
}
