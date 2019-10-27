#include "CombatComponent.hpp"
#include "../Akuma/CombatLog.hpp"
#include "Akuma/Items/ItemManager.hpp"
#include "Stonk/Engine.hpp"
#include "EquipmentComponent.hpp"
#include "StatComponent.hpp"
#include "TurnComponent.hpp"

/**
 * @brief  Default Constructor
 */
CombatComponent::CombatComponent()  = default;

/**
 * @brief  Default Destructor
 */
CombatComponent::~CombatComponent() = default;

/**
 * @brief  Loads combat audio
 */
void CombatComponent::init() {
    this->audiomgr   = &(Stonk::Engine::get().audio);
    this->combatSound = audiomgr->LoadSound("hit.ogg");
    this->naturalCritSound = audiomgr->LoadSound("natural_crit.ogg");
    this->critSound      = audiomgr->LoadSound("crit.ogg");
}

/**
 * @brief  Unused
 */
void CombatComponent::update() {}

/**
 * @brief  Unused
 */
void CombatComponent::draw() {}

/**
 * @brief  Attacks an entity and determines what type of combat to be used
 * @param opponent a pointer to the opponent attacking
 */
void CombatComponent::attackEntity(Entity *opponent) {
    singleHanded(opponent);
 
    this->entity->getComponent<TurnComponent>().endYourTurn();
}

/**
 * @brief  Single handed combat
 * @param opponent a pointer to the opponent attacking
 */
void CombatComponent::singleHanded(Entity *opponent) {
    auto enemyArmor = ItemManager::getArmor(
        opponent->getComponent<EquipmentComponent>().getEquippedArmor().itemID);

    auto mainHand = ItemManager::getWeapon(
        this->entity->getComponent<EquipmentComponent>().getEquippedMainHand().itemID);

    int diceRoll =
        diceroller.Roll(1, 20) + this->entity->getComponent<StatComponent>().getDexterityMod();
    if (this->entity->hasComponent<EquipmentComponent>()) {
        auto e =
            this->entity->getComponent<EquipmentComponent>().getEquippedArmor().itemID;
        diceRoll -= ItemManager::getArmor(e).dexPentalty;
            
	}
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
            this->audiomgr->PlaySound(this->naturalCritSound);
        } else {
            damage = weaponDamage(weaponPreHitDie, weaponHitDie);
            logInformation(damage, opponent, mainHand);
            this->audiomgr->PlaySound(this->combatSound);
            // regular damage
        }
    } else if (diceRoll >= ((enemyAC + enemyDodge) - enemyDodgePenalty)) {
        if (diceRoll >= critrange) {
            damage =
                weaponDamage(weaponPreHitDie, weaponHitDie, weaponCritMultiplier);
            logInformation(damage, opponent, mainHand);
            this->audiomgr->PlaySound(this->critSound);
            // damage multiplier
        } else {
            damage = weaponDamage(weaponPreHitDie, weaponHitDie);
            logInformation(damage, opponent, mainHand);
            this->audiomgr->PlaySound(this->combatSound);
            // regular damage
        }
    } else {
        string info = this->entity->getComponent<StatComponent>().stat.name +
                      " misses their attack on " +
                      opponent->getComponent<StatComponent>().stat.name + ".";
        logInformation(info);
    }
    if (damage > 0) {
        opponent->getComponent<StatComponent>().takeDamage(damage);
	}
    opponent->getComponent<StatComponent>().deathTrigger();
}

/**
 * @brief  Overloaded function to determine the total damage
 * @param  weaponPreHitDie the amount of die to roll
 * @param  weaponHitDie The total sides of the dice
 * @return the total damage deal to the entity
 */
int CombatComponent::weaponDamage(int weaponPreHitDie, int weaponHitDie) {
    return weaponDamage(weaponPreHitDie, weaponHitDie, 1);
}

/**
 * @brief  Determine the total damage
 * @param  weaponPreHitDie the amount of die to roll
 * @param  WeaponHitDie The total sides of the dice
 * @param  weaponCritMultiplier determine how many times to roll if critted
 * @return the total damage deal to the entity
 */
int CombatComponent::weaponDamage(int weaponPreHitDie, int weaponHitDie,
                                  int weaponCritMultiplier) {
    int totalDamage = 0;
    for (int x = 0; x < weaponCritMultiplier; x++) {
        totalDamage += diceroller.Roll(weaponPreHitDie, weaponHitDie);
    }
    return totalDamage;
}

/**
 * @brief  Attack an an entity from a given node
 * @param  opponentSquare a pointer to the node
 */
void CombatComponent::attackEntity(Pathing::Node *opponentSquare) {
    attackEntity(opponentSquare->occupant);
}

/**
 * @brief  Logs information to the combat log
 * @param  damage the damage to be logged
 * @param  opponent the entity that was attacked
 */
void CombatComponent::logInformation(int damage, Entity *opponent) {
    string eventLog =
        this->entity->getComponent<StatComponent>().stat.name +
        "hit " + opponent->getComponent<StatComponent>().stat.name + " for " +
        std::to_string(damage) + " points of damage.";
    logInformation(eventLog);
}

/**
 * @brief  Logs information to the combat log
 * @param  damage the damage to be logged
 * @param  opponent the entity that was attacked
 * @param  weapon the weapon used to attack
 */
void CombatComponent::logInformation(int damage, Entity *opponent, Weapon weapon) {
    string eventLog =
        "Combat: Name: " + this->entity->getComponent<StatComponent>().stat.name +
        " hit " + opponent->getComponent<StatComponent>().stat.name + " with " + weapon.name
        +" for " + std::to_string(damage) + " points of damage.";
    logInformation(eventLog);
}

/**
 * @brief  Logs information to the combat log
 * @param info the output to the screen
 */
void CombatComponent::logInformation(string info) {
    CombatLog::log().push_back(info);
}
