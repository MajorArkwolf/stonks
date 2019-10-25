#include "CombatComponent.hpp"
#include "../Akuma/CombatLog.hpp"


#include "EquipmentComponent.hpp"
#include "StatComponent.hpp"
#include "TurnComponent.hpp"

CombatComponent::CombatComponent()  = default;
CombatComponent::~CombatComponent() = default;

void CombatComponent::init() {
    if (!this->entity->hasComponent<EquipmentComponent>()) {
        this->entity->addComponentID<EquipmentComponent>();
	}
}
void CombatComponent::update() {}
void CombatComponent::draw() {}

void CombatComponent::attackEntity(Entity *opponent) {
	//Add dual hand and single handed combat
    singleHanded(opponent);
 
    this->entity->getComponent<TurnComponent>().endYourTurn();
}

void CombatComponent::singleHanded(Entity *opponent) {
    auto enemyArmor = ItemManager::getArmor(
        opponent->getComponent<EquipmentComponent>().getEquippedArmor().itemID);
    //   if (/*this->entity->getComponent<EquipmentComponent>().getEquippedOffHand().type() == shield*/) {
    //       auto &enemyShield =
    //           opponent->getComponent<EquipmentComponent>().getEquippedOffHand();
    //    }
    auto mainHand = ItemManager::getWeapon(
        this->entity->getComponent<EquipmentComponent>().getEquippedMainHand().itemID);
    // auto &offHand = ItemManager::getWeapon(
    //    this->entity->getComponent<EquipmentComponent>().getEquippedOffHand().itemID);

    int diceRoll             = diceroller.Roll(1, 20);
    int weaponHitDie         = mainHand.weaponHitDie;
    int weaponPreHitDie      = mainHand.weaponPreHitDie;
    int weaponCritMultiplier = mainHand.critMultiplier;
    int enemyAC              = enemyArmor.armorBonus;
    int enemyDodge = opponent->getComponent<StatComponent>().stat.dexterity;
    int weaponCritRange   = mainHand.critRange;
    int enemyDodgePenalty = enemyArmor.dexPentalty;
    int critrange         = 20 - weaponCritRange -
                    this->entity->getComponent<StatComponent>().getLuckMod();
    int damage = 0;

    if (diceRoll == 1) {
        logInformation(this->entity->getComponent<StatComponent>().stat.name +
                       " fumbles their attack.");
    } else if (diceRoll == 20) {
        diceRoll = diceroller.Roll(1, 20);
        if (diceRoll >= ((enemyAC + enemyDodge) - enemyDodgePenalty)) {
            // natural 20 crit damage
            damage =
                weaponDamage(weaponPreHitDie, weaponHitDie, weaponCritMultiplier);
            logInformation(damage, opponent, mainHand);
        } else {
            damage = weaponDamage(weaponPreHitDie, weaponHitDie);
            logInformation(damage, opponent, mainHand);
            // regular damage
        }
    } else if (diceRoll >= ((enemyAC + enemyDodge) - enemyDodgePenalty)) {
        if (diceRoll >= critrange) {
            damage =
                weaponDamage(weaponPreHitDie, weaponHitDie, weaponCritMultiplier);
            logInformation(damage, opponent, mainHand);
            // damage multiplier
        } else {
            damage = weaponDamage(weaponPreHitDie, weaponHitDie);
            logInformation(damage, opponent, mainHand);
            // regular damage
        }
    } else {
        string info = this->entity->getComponent<StatComponent>().stat.name +
                      " misses their attack on" +
                      opponent->getComponent<StatComponent>().stat.name + ".";
        logInformation(info);
    }
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

void CombatComponent::logInformation(int damage, Entity *opponent, Weapon weapon) {
    string eventLog =
        "Combat: Name: " + this->entity->getComponent<StatComponent>().stat.name +
        " hit " + opponent->getComponent<StatComponent>().stat.name + " with " + weapon.name
        +" for " + std::to_string(damage) + " points of damage.";
    logInformation(eventLog);
}

void CombatComponent::logInformation(string info) {
    CombatLog::log().push_back(info);
}
