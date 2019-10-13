#include "Node.hpp"

Pathing::Node::Node() {
    x      = 0;
    y      = 0;
    parent = nullptr;
}

int Pathing::Node::fCost() const {
    return this->gCost + this->hCost;
}

bool Pathing::Node::operator<(const Node &rhs) const {

    if (fCost() == rhs.fCost()) {
        return hCost < rhs.hCost;
    } else {
        return fCost() < rhs.fCost();
    }
}

bool Pathing::Node::operator==(const Node &rhs) const {
    return (x == rhs.x && y == rhs.y);
}

auto Pathing::Node::toggleWalkable() -> void {
    this->walkable = (this->walkable) ? 0 : 1;
}

auto Pathing::Node::setWalkable(bool _walkable) -> void {
    walkable = _walkable;
}
