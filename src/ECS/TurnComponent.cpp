#include "TurnComponent.hpp"

/**
 * @brief  Defaulted Constructor
 */
TurnComponent::TurnComponent()  = default;

/**
 * @brief  Defaulted Destructor
 */
TurnComponent::~TurnComponent() = default;

/**
 * @brief  Unused
 */
void TurnComponent::init() {}

/**
 * @brief  Unused
 */
void TurnComponent::update() {}

/**
 * @brief  Unused
 */
void TurnComponent::draw() {}

/**
 * @brief  Checks to see if the opponent has concluded there entire turn
 * @return End of Turn
*/
bool TurnComponent::checkTurn() {
    return this->turnPhase2;
}

/**
 * @brief  Lets the entity begin there turn, enabling them to do a single action.
 */
void TurnComponent::startYourTurn() {
    this->isTurn     = true;
    this->turnPhase2 = true;
}

/**
 * @brief  Marks that entities has assigned there action but the action has not concluded
 */
void TurnComponent::assignAction() {
    this->isTurn = false;
}

/**
 * @brief  This will force conclude there turn, makes sure both values are false so they can not act at all.
 */
void TurnComponent::endYourTurn() {
    this->isTurn     = false;
    this->turnPhase2 = false;
}
