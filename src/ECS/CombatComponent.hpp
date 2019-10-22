#pragma once
#include <iostream>
#include "../Akuma/Pathing/Node.hpp"
#include "../Akuma/RNG/Dice.hpp"
#include "ECS.hpp"
#include "StatComponent.hpp"
#include "TurnComponent.hpp"
#include "../Akuma/CombatLog.hpp"

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
        int damage = 0;
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
					//natural 20 crit damage
                    damage = weaponDamage(weaponPreHitDie, weaponHitDie,
                                          weaponCritMultiplier);
                } else {
                    damage = weaponDamage(weaponPreHitDie, weaponHitDie);
                    // regular damage
                }
            } else if (diceRoll >= ((enemyAC + enemyDodge) - enemyDodgePenalty)) {
                if (diceRoll >= critrange) {
                    damage = weaponDamage(weaponPreHitDie, weaponHitDie,
                                        weaponCritMultiplier);
                    // damage multiplier
                } else {
                    damage = weaponDamage(weaponPreHitDie, weaponHitDie);
                    // regular damage
                }
            } else {
				//miss
                std::cout << "miss \n";
            }
        }
        logInformation(damage, opponent);
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

	void logInformation(int damage, Entity *opponent) {
        string eventLog =
            "Combat: Name: " + this->entity->getComponent<StatComponent>().stat.name +
            "hit " + opponent->getComponent<StatComponent>().stat.name +
            " for " +
            std::to_string(damage) + " points of damage.";
        CombatLog::log().push_back(eventLog);
	}
};
