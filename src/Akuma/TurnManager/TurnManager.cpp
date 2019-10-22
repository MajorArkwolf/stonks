#include "TurnManager.hpp"
#include "../RNG/Dice.hpp"
#include "../../ECS/TurnComponent.hpp"
#include "../../ECS/StatComponent.hpp"

void TurnManager::update() {}

void TurnManager::addEntity(Entity * newEntity) {
    EntityInfo newActor;
    Dice diceroller;
    newActor.entity = newEntity;
    newActor.inititive =
        diceroller.Roll(1, 20) +
        newEntity->getComponent<StatComponent>().getDexterityMod();
    actors.push_back(newActor);
    sortActors();
}

void TurnManager::sortActors() {}