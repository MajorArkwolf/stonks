#include "CombatComponent.hpp"
#include "Akuma/Items/ItemManager.hpp"

CombatComponent::CombatComponent()  = default;
CombatComponent::~CombatComponent() = default;

void CombatComponent::init() {}
void CombatComponent::update() {}
void CombatComponent::draw() {}

void CombatComponent::attackEntity(Entity *opponent) {
    // weaponCrit
    // WeaponDamage
    int diceRoll             = diceroller.Roll(1, 20);
    int weaponHitDie         = 3;
    int weaponPreHitDie      = 1;
    int weaponCritMultiplier = 3;
    int enemyAC              = 0;
    int enemyDodge = opponent->getComponent<StatComponent>().stat.dexterity;
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
            logInformation(this->entity->getComponent<StatComponent>().stat.name + " fumbles their attack.");
        } else if (diceRoll == 20) {
            diceRoll = diceroller.Roll(1, 20);
            if (diceRoll >= ((enemyAC + enemyDodge) - enemyDodgePenalty)) {
                // natural 20 crit damage
                damage = weaponDamage(weaponPreHitDie, weaponHitDie,
                                      weaponCritMultiplier);
                logInformation(damage, opponent);
            } else {
                damage = weaponDamage(weaponPreHitDie, weaponHitDie);
                logInformation(damage, opponent);
                // regular damage
            }
        } else if (diceRoll >= ((enemyAC + enemyDodge) - enemyDodgePenalty)) {
            if (diceRoll >= critrange) {
                damage = weaponDamage(weaponPreHitDie, weaponHitDie,
                                      weaponCritMultiplier);
                logInformation(damage, opponent);
                // damage multiplier
            } else {
                damage = weaponDamage(weaponPreHitDie, weaponHitDie);
                logInformation(damage, opponent);
                // regular damage
            }
        } else {
            logInformation(this->entity->getComponent<StatComponent>().stat.name +
                           " misses their attack on" +
                           opponent->getComponent<StatComponent>().stat.name +
                           ".");
        }
    }    
    this->entity->getComponent<TurnComponent>().endYourTurn();
}
int CombatComponent::weaponDamage(int weaponPreHitDie, int weaponHitDie) {
    return weaponDamage(weaponPreHitDie, weaponHitDie, 1);
}

int CombatComponent::weaponDamage(int weaponPreHitDie, int weaponHitDie,
                                  int weaponCritMultiplier) {
    int totalDamage = 0;
    for (int x = 0; x < weaponCritMultiplier; x++) {
        totalDamage += diceroller.Roll(weaponPreHitDie, weaponHitDie);
    }
    return totalDamage;
}

void CombatComponent::attackEntity(Pathing::Node *opponentSquare) {
    attackEntity(opponentSquare->occupant);
}

void CombatComponent::logInformation(int damage, Entity *opponent) {
    string eventLog =
        "Combat: Name: " + this->entity->getComponent<StatComponent>().stat.name +
        "hit " + opponent->getComponent<StatComponent>().stat.name + " for " +
        std::to_string(damage) + " points of damage.";
    logInformation(eventLog);
}

void CombatComponent::logInformation(string info) {
    CombatLog::log().push_back(info);
}
