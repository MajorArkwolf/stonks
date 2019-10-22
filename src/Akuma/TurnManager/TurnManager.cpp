#include "TurnManager.hpp"
#include "../RNG/Dice.hpp"
#include "../../ECS/TurnComponent.hpp"
#include "../../ECS/StatComponent.hpp"

void TurnManager::update() {
    if (turnManagerSwitch) {
        if (turnToken) {
            if (actors.size() > actorTurnID) {
                actors.at(actorTurnID).entity->getComponent<TurnComponent>().startYourTurn();
                turnToken = false;
            } else {
                actorTurnID = 0;
                roundCounter++;
            }
        } else {
            if (!actors.at(actorTurnID).entity->getComponent<TurnComponent>().checkTurn()) {
                turnToken = true;
                actorTurnID++;
            }
		}
    }

}

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

void TurnManager::giveTokenToEntity(Entity *entity) {
    if (entity->hasComponent<TurnComponent>()) {
        entity->getComponent<TurnComponent>().startYourTurn();
        turnToken = false;
	}
}

void TurnManager::checkEntityTurnState(Entity *entity) {
    if (entity->hasComponent<TurnComponent>()) {
        if (!entity->getComponent<TurnComponent>().checkTurn()) {
            turnToken = true;
        }
    }
}

void TurnManager::turnOnManager() {
    turnManagerSwitch = true;
}

void TurnManager::turnOffManager() {
    turnManagerSwitch = false;
}
