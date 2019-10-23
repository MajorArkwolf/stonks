#include "TurnComponent.hpp"
void TurnComponent::init() {}
void TurnComponent::update() {}
void TurnComponent::draw() {}

bool TurnComponent::checkTurn() {
    return this->turnPhase2;
}
void TurnComponent::startYourTurn() {
    this->isTurn     = true;
    this->turnPhase2 = true;
}
void TurnComponent::assignAction() {
    this->isTurn = false;
}
void TurnComponent::endYourTurn() {
    this->isTurn     = false;
    this->turnPhase2 = false;
}
