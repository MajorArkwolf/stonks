#pragma once

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
				//You fumbled
            }else if (diceRoll == 20) {
                diceRoll = diceroller.Roll(1, 20);
                if (diceRoll >= ((enemyAC + enemyDodge) - enemyDodgePenalty)) {
                    // crit damage
                } else {
                    // regular damage
                }
            } else if (diceRoll >= ((enemyAC + enemyDodge) - enemyDodgePenalty)) {
                if (diceRoll >= critrange) {
                    // damage multiplier
                } else {
                    // regular damage
                }
            }
        }
        this->entity->getComponent<TurnComponent>().endYourTurn();
    }

    int weaponDamage(int weaponHitDie, int weaponPreHitDie,
                     int weaponCritMultiplier) {
        int totalDamage = 0;
        for (int i = 0; i < weaponPreHitDie; i++) {
			
		}

        return totalDamage;
    }

    void attackEntity(Pathing::Node *opponentSquare) {
        attackEntity(opponentSquare->occupant);
    }

  private:
    Dice diceroller;
    Entity *opponent = nullptr;
    bool turnToken   = false;
};
