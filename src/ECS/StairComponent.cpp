#include "StairComponent.hpp"
bool StairComponent::checkStairActive() {
    return stairCaseActivate;
}
void StairComponent::SetStairActive() {
    stairCaseActivate = true;
}

void StairComponent::resetStairCase() {
	stairCaseActivate = false;
    occupiedNodes[0]->occupied = false;
    occupiedNodes[0]  = nullptr;
    occupiedNodes[1]->occupied = false;
    occupiedNodes[1]  = nullptr;
    occupiedNodes[2]->occupied = false;
    occupiedNodes[2]  = nullptr;
    occupiedNodes[3]->occupied = false;
    occupiedNodes[3]  = nullptr;
}

void StairComponent::setNodes(Pathing::Node *node1, Pathing::Node *node2,
                            Pathing::Node *node3, Pathing::Node *node4) {
    node1->occupied  = true;
    node1->occupant  = this->entity;
    node2->occupied  = true;
    node2->occupant  = this->entity;
    node3->occupied  = true;
    node3->occupant  = this->entity;
    node4->occupied  = true;
    node4->occupant  = this->entity;
	occupiedNodes[0] = node1;
    occupiedNodes[1] = node2;
    occupiedNodes[2] = node3;
    occupiedNodes[3] = node4;
}