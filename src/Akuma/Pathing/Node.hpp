#pragma once

/**
 * @namespace Pathing
 * @brief A namespace for the A* pathfinding algorithm
 */
namespace Pathing {

    /**
     * @class Node
     * @brief A class for representing a grid space on the grid
     */
    class Node {
      public:
        Node();
        Node(unsigned _x, unsigned _y);

        /// Parent node for pathfinding algorithm
        Node *parent = nullptr;
        /// gCost + hCost;
        int fCost() const;
        /// Distance from end node
        int hCost = 0;
        /// Distance from starting node
        int gCost = 0;
        /// X location in grid
        unsigned x = 0;
        /// Y location in grid
        unsigned y = 0;
        /// If node is traversable then walkable == 1
        bool walkable = 1;

        auto toggleWalkable() -> void;
        auto setWalkable(bool _walkable) -> void;
    };
};
