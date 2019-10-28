#include "StatComponent.hpp"
#include "PlayerComponent.hpp"
#include "EnemyComponent.hpp"
#include "DeadComponent.hpp"

/**
 * @brief  Defaulted Constructor
 */
StatComponent::StatComponent()  = default;

/**
 * @brief  Defaulted Destructor
 */
StatComponent::~StatComponent() = default;

/**
 * @brief   Alternate Constructor
 * @param   newStat CharacterSheet
 */
StatComponent::StatComponent(CharacterSheet newStat) {
    this->stat = newStat;
}

/**
 * @brief  Unused
 */
void StatComponent::init() {}

/**
 * @brief  Unused
 */
void StatComponent::update() {}

/**
 * @brief  Unused
 */
void StatComponent::draw() {}

/**
 * @brief  Used to determine the modifier of Strength
 * @return Strength Modifier
 */
auto StatComponent::getStrengthMod() -> int {
    return getMod(this->stat.strength);
}

/**
 * @brief  Used to determine the modifier of Intelligence
 * @return Intelligence Modifier
 */
auto StatComponent::getIntelligenceMod() -> int {
    return getMod(this->stat.intelligence);
}

/**
 * @brief  Used to determine the modifier of Dexterity
 * @return Dexterity Modifier
 */
auto StatComponent::getDexterityMod() -> int {
    return getMod(this->stat.dexterity);
}

/**
 * @brief  Used to determine the modifier of Luck
 * @return Luck Modifier
 */
auto StatComponent::getLuckMod() -> int {
    return getMod(this->stat.luck);
}

/**
 * @brief  Used to determine the modifier of Vitality
 * @return Vitality Modifier
 */
auto StatComponent::getVitalityMod() -> int {
    return getMod(this->stat.vitality);
}


/**
 * @brief  getter for stat sheet
 * @return Stat sheet, Character shet
 */
auto StatComponent::getStatSheet() -> CharacterSheet & {
    return stat;
}


/**
 * @brief  setter for stat sheet
 * @param newStat CharacterSheet
 */
auto StatComponent::setStatSheet(CharacterSheet newStat) -> void {
    this->stat = newStat;
}


/**
 * @brief  Calculates Modifer, hard coded
 * @return Modifier of any given stat
 */
auto StatComponent::getMod(int checkStat) -> int {
    if (checkStat <= 1) {
        return -5;
    } else if (checkStat < 4) {
        return -4;
    } else if (checkStat < 6) {
        return -3;
    } else if (checkStat < 8) {
        return -2;
    } else if (checkStat < 10) {
        return -1;
    } else if (checkStat < 12) {
        return 0;
    } else if (checkStat < 14) {
        return 1;
    } else if (checkStat < 16) {
        return 2;
    } else if (checkStat < 18) {
        return 3;
    } else if (checkStat < 20) {
        return 4;
    } else if (checkStat < 22) {
        return 5;
    } else if (checkStat < 24) {
        return 6;
    } else if (checkStat < 26) {
        return 7;
    } else if (checkStat < 28) {
        return 8;
    } else if (checkStat < 30) {
        return 9;
    } else if (checkStat > 30) {
        return 10;
    } else {
        return 0;
    }
}

/**
 * @brief  Sets the HP of the entity based of there level
 *
*/
auto StatComponent::setupEntity() -> void {
    for (auto i = 1; i <= this->stat.level; i++) {
        if (i == 1) {
            this->stat.maxHP = this->stat.HD + getVitalityMod();
        } else {
            this->stat.maxHP +=
                this->diceroller.Roll(1, this->stat.HD) + getVitalityMod();
        }
	}
    this->stat.HP = this->stat.maxHP;
}

/**
 * @brief  Removes HP of the given entity
 *
 */
auto StatComponent::takeDamage(int damage) -> void {
    this->stat.HP -= damage;
}

/**
 * @brief  Checks to see if the entity should be dead and then proceeds to kill them if true
 *
 */
auto StatComponent::deathTrigger() -> void {
    if (this->stat.HP < 0 && !this->stat.dead) {
        this->stat.dead = true;
		if (this->entity->hasComponent<PlayerComponent>()) {
            this->entity->addComponentID<DeadComponent>();
		} else if (this->entity->hasComponent<EnemyComponent>()) {
            this->entity->getComponent<EnemyComponent>().deadEnemy();
		}
    }
}

/**
 * @brief  checks if the entity has leveled up then gives them a point
 *
 */
auto StatComponent::expCheck() -> void {
    if (this->stat.exp > 100) {
        this->stat.exp -= 100;
        this->stat.pointsLeft++;
        this->stat.level++;
    }
}

/**
 * @brief  Adds a point into strength value
 */
auto StatComponent::pointStrength() -> void {
    this->stat.strength++;
    newMaxHP();
}

/**
 * @brief  Adds a point into dexterity value
 */
auto StatComponent::pointDexterity() -> void {
    this->stat.dexterity++;
    newMaxHP();
}

/**
 * @brief  Adds a point into luck value
 */
auto StatComponent::pointLuck() -> void {
    this->stat.luck++;
    newMaxHP();
}

/**
 * @brief  Adds a point into intelligence value
 */
auto StatComponent::pointIntelligence() -> void {
    this->stat.intelligence++;
    newMaxHP();
}

/**
 * @brief  If there is a change in mod, will add several hitpoints on top of the ones they get for the level.
 */
auto StatComponent::pointVitality() -> void {
    auto e = getVitalityMod();
    this->stat.vitality++;
    if (e != getVitalityMod()) {
        this->stat.maxHP += this->stat.level;
	}
    newMaxHP();
}

/**
 * @brief  Levels up the player
 */
auto StatComponent::levelUp() -> void {
    this->stat.level++;
    this->stat.pointsLeft++;
}

/**
 * @brief  adds additional points to the players hp
 */
auto StatComponent::newMaxHP() -> void {
    this->stat.maxHP += diceroller.Roll(1, this->stat.HD) + getVitalityMod();
}
