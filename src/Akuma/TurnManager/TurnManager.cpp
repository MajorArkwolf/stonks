#include "TurnManager.hpp"

#include <algorithm>
#include <functional>
#include <string>

#include "../../ECS/DeadComponent.hpp"
#include "../../ECS/StatComponent.hpp"
#include "../../ECS/TurnComponent.hpp"
#include "../RNG/Dice.hpp"
#include "Akuma/CombatLog.hpp"

using std::string;

void TurnManager::update() {
    if (turnManagerSwitch) {
        if (turnToken) {
            if (actors.size() > actorTurnID) {
                if (!actors.at(actorTurnID).entity->hasComponent<DeadComponent>()) {
                    actors.at(actorTurnID).entity->getComponent<TurnComponent>().startYourTurn();
                    turnToken = false;
                } else {
                    actorTurnID++;
				}
            } else {
                actorTurnID = 0;
                roundCounter++;
                /*CombatLog::log().push_back(
                   "-----" + std::to_string(roundCounter) + "-----");*/
            }
        } else {
            if (!actors.at(actorTurnID).entity->getComponent<TurnComponent>().checkTurn()) {
                turnToken = true;
                actorTurnID++;
            } else if (actors.at(actorTurnID).entity->hasComponent<DeadComponent>()) {
                actors.at(actorTurnID).entity->getComponent<TurnComponent>().endYourTurn();
                turnToken = true;
                actorTurnID++;
            }
        }
    }
}

void TurnManager::addEntity(Entity *newEntity) {
    EntityInfo newActor;
    Dice diceroller;
    newActor.entity = newEntity;
    newActor.currentDexMod =
        newEntity->getComponent<StatComponent>().getDexterityMod();
    newActor.inititive = diceroller.Roll(1, 20) + newActor.currentDexMod;
    actors.push_back(newActor);
    sortActors();
}

void TurnManager::sortActors() {
    std::sort(actors.begin(), actors.end());
}

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
    if (roundCounter == 1) {
        //CombatLog::log().push_back("-----" + std::to_string(roundCounter) + "-----");
    }
    turnToken = true;
}

void TurnManager::clearActors() {
    actors.clear();
}

void TurnManager::turnOffManager() {
    turnManagerSwitch = false;
}

void TurnManager::checkDexChange() {
    bool sortArray = false;
    for (auto &e : actors) {
        if (e.currentDexMod !=
            e.entity->getComponent<StatComponent>().getDexterityMod()) {
            Dice diceroller;
            sortArray = true;
            e.currentDexMod =
                e.entity->getComponent<StatComponent>().getDexterityMod();
            e.inititive = diceroller.Roll(1, 20) + e.currentDexMod;
        }
    }
    if (sortArray) {
        sortActors();
    }
}

int TurnManager::getTurnRound() {
    return roundCounter;
}
