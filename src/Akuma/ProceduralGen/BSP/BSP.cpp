#include "BSP.hpp"

#include <cmath>
#include <iostream>
#include <random>

#include <glm/vec2.hpp>

using BSP::Node;

/**
 * @brief Default constructor for BSP Tree
 * Sets root to nullptr
 */
BSP::BSPTree::BSPTree() {
    root = nullptr;
}

/**
 * @brief Overloaded constructor for BSP Tree
 * @param size Size of square to partition
 * @param subdivisions Amount of times to subdivide base square, number of rooms = 2^subdivisions
 */
BSP::BSPTree::BSPTree(glm::uvec2 size, int subdivisions) {
    glm::uvec2 bottomLeft = {1, 1};
    glm::uvec2 topRight   = {size.x, size.y};
    root                  = new Node(bottomLeft, topRight);

    populateTree(root, subdivisions);
    splitNode(root);
    traverse(root);
}

/**
 * @brief Destructor for BSP tree
 * Safely destructs tree and frees memory
 */
BSP::BSPTree::~BSPTree() {
    delete (root);
    root = nullptr;
}

/**
 * @brief Assignment operator overload for BSPTree
 * Safely performs a deep copy from left hand tree to right hand tree
 * @param rhs BSPTree on right hand side
 * @return Copied tree
 */
const BSP::BSPTree &BSP::BSPTree::operator=(const BSPTree &rhs) {
    if (this != &rhs) {
        if (root != nullptr) {
            delete (root);
        }
        if (rhs.root == nullptr) {
            root = nullptr;
        } else {
            copyTree(root, rhs.root);
        }
    }

    return *this;
}

/**
 * @brief Copy constructor for BSPTree
 * @param other Tree to deep copy this tree into
 */
BSP::BSPTree::BSPTree(const BSPTree &other) {
    copyTree(this->root, other.root);
}

/**
 * @brief Safely destructs tree by calling root node destructor
 * Causes destruction cascade due to node destructor
 */
void BSP::BSPTree::deleteTree() {
    delete (root);
    root = nullptr;
}

/**
 * @brief Regenerates current BSP based on passed in parameters
 * @param size Size of square to partition
 * @param subdivisions Amount of times to subdivide base square, number of rooms = 2^subdivisions
 */
void BSP::BSPTree::reGen(glm::vec2 size, int subdivisions) {
    deleteTree();

    glm::vec2 bottomLeft = {0, 0};
    glm::vec2 topRight   = {size.x, size.y};
    root                 = new Node(bottomLeft, topRight);

    populateTree(root, subdivisions);
    splitNode(root);
    traverse(root);
}

/**
 * @brief Recursive function used to generate tree nodes and subdivide rooms
 * @param node Current node being worked on
 * @param subdivisions Amount of times to subdivide base square, number of rooms = 2^subdivisions
 */
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

/**
 * @brief Returns all rooms in tree
 * @return A stl vector containing all Nodes in the tree that have no children (rooms)
 */
std::vector<Node *> BSP::BSPTree::getRooms() {
    std::vector<Node *> roomList;

    traverse(root, roomList);

    return roomList;
}

/**
 * @brief Splits the given node semi randomly and creates children
 * @param node Node to split
 */
bool BSP::BSPTree::splitNode(BSP::Node *node) {

    bool vertical = 1;
    unsigned cutoffRange =
        30; // Needs to be between 10 and 40 for best results, higher = more random room sizes

    std::random_device dev;
    std::mt19937 rng(dev());
    std::uniform_int_distribution<std::mt19937::result_type> dist(1, 100);

    auto parentSize = node->gridTopRight - node->gridBottomLeft;

    // if (dist(rng) > 50) {
    //    vertical = 0;
    //}
    if ((parentSize.x / parentSize.y) < 1.5f) {
        vertical = 0;
    }
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

/**
 * @brief Tree traversal function used by getRooms to push nodes without children onto vector
 * @param node Current node being looked at
 * @param list The vector to push childless nodes onto
 */
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

/**
 * @brief Method used to deep copy one tree to another
 * @param copiedTreeRoot Root node of tree being copied
 * @param otherTreeRoot Root node of tree being copied into
 */
void BSP::BSPTree::copyTree(Node *&copiedTreeRoot, Node *otherTreeRoot) {
    if (otherTreeRoot == nullptr)
        copiedTreeRoot = nullptr;
    else {
        copiedTreeRoot                 = new Node;
        copiedTreeRoot->gridBottomLeft = otherTreeRoot->gridBottomLeft;
        copiedTreeRoot->gridTopRight   = otherTreeRoot->gridTopRight;
        copiedTreeRoot->depth          = otherTreeRoot->depth;
        copyTree(copiedTreeRoot->left, otherTreeRoot->left);
        copyTree(copiedTreeRoot->right, otherTreeRoot->right);
    }
}

/**
 * @brief Tree traversal method, does nothing but traverse
 * @param node Current node
 */
int BSP::BSPTree::traverse(BSP::Node *node) {

    if (node == nullptr) {
        return 0;
    }

    if (node->left != nullptr) {
        traverse(node->left);
    }

    if (node->right != nullptr) {
        traverse(node->right);
    }

    return 0;
}
