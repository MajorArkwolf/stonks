#pragma once
#include <iostream>
#include "../Akuma/Pathing/Node.hpp"
#include "../Akuma/RNG/Dice.hpp"
#include "ECS.hpp"
#include "StatComponent.hpp"
#include "TurnComponent.hpp"

class CombatComponent : public Component {
  public:
    CombatComponent()  = default;
    ~CombatComponent() = default;
    void init() {}
    void update() {}
    void draw() {}

    void attackEntity(Entity *opponent) {
        // weaponCrit
        // WeaponDamage
        int diceRoll             = diceroller.Roll(1, 20);
        int weaponHitDie         = 3;
        int weaponPreHitDie      = 1;
        int weaponCritMultiplier = 3;
        int enemyAC              = 0;
        int enemyDodge           = 0;
        int weaponCritRange      = 0;
        int enemyDodgePenalty    = 0;
        int critrange            = 20 - weaponCritRange -
                        this->entity->getComponent<StatComponent>().getLuckMod();
        if (opponent->hasComponent<StatComponent>()) {
            if (false /*opponent->hasComponent<EquipmentComponent>()*/) {
                // enemyAC =
                // enemyDodgePenalty
            }
            if (diceRoll == 1) {
                std::cout << "fumble \n";
            } else if (diceRoll == 20) {
                diceRoll = diceroller.Roll(1, 20);
                if (diceRoll >= ((enemyAC + enemyDodge) - enemyDodgePenalty)) {
                    std::cout << weaponDamage(weaponPreHitDie, weaponHitDie,
                                              weaponCritMultiplier)
                              << " ";
                    std::cout << "natural crit hit \n";
                } else {
                    std::cout << weaponDamage(weaponPreHitDie, weaponHitDie)
                              << " ";
                    std::cout << "natural crit miss \n";
                    // regular damage
                }
            } else if (diceRoll >= ((enemyAC + enemyDodge) - enemyDodgePenalty)) {
                if (diceRoll >= critrange) {
                    std::cout << weaponDamage(weaponPreHitDie, weaponHitDie,
                                              weaponCritMultiplier)
                              << " ";
                    std::cout << "normal hit crit \n";
                    // damage multiplier
                } else {
                    std::cout << weaponDamage(weaponPreHitDie, weaponHitDie) << " ";
                    std::cout << "normal hit \n";
                    // regular damage
                }
            } else {
                std::cout << "miss \n";
            }
        }
        this->entity->getComponent<TurnComponent>().endYourTurn();
    }
    int weaponDamage(int weaponPreHitDie, int weaponHitDie) {
        return weaponDamage(weaponPreHitDie, weaponHitDie, 1);
    }

    int weaponDamage(int weaponPreHitDie, int weaponHitDie,
                     int weaponCritMultiplier) {
        int totalDamage = 0;
        for (int x = 0; x < weaponCritMultiplier; x++) {
            totalDamage += diceroller.Roll(weaponPreHitDie, weaponHitDie);
        }
        return totalDamage;
    }

    void attackEntity(Pathing::Node *opponentSquare) {
        attackEntity(opponentSquare->occupant);
    }

  private:
    Dice diceroller;
};
