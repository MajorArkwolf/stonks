#pragma once
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>

using std::ifstream;
using std::istream;
using std::stringstream;

using std::string;
using std::vector;

enum itemType { consumable, armor, weapon, empty };
enum rarityItem { common, uncommon, rare, mythic };
enum mainStat { strength, agility, intelligence };

struct ItemID {
    size_t itemID      = 0;
    itemType type      = empty;
    string name        = "";
    string description = "";
};

struct Armor {
    size_t itemID      = 0;
    itemType type      = armor;
    string name        = "";
    string description = "";
    rarityItem rarity  = common;
    int armorBonus     = 0;
    int dexPentalty    = 0;
    friend istream &operator>>(std::istream &input, Armor &item) {
        string inputString              = "";
        static constexpr char SEPARATOR = ',';
        std::getline(input, inputString, SEPARATOR);
        item.name = inputString;

        std::getline(input, inputString, SEPARATOR);
        item.description = inputString;

        std::getline(input, inputString, SEPARATOR);
        if (inputString == "common") {
            item.rarity = common;
        } else if (inputString == "uncommon") {
            item.rarity = uncommon;
        } else if (inputString == "rare") {
            item.rarity = rare;
        } else if (inputString == "mythic") {
            item.rarity = mythic;
        }
        std::getline(input, inputString, SEPARATOR);
        item.armorBonus = std::stoi(inputString);

        std::getline(input, inputString, SEPARATOR);
        item.dexPentalty = std::stoi(inputString);

        return input;
    }
};

struct Weapon {
    size_t itemID         = 0;
    itemType type         = weapon;
    string name           = "";
    string description    = "";
    rarityItem rarity     = common;
    int weaponPreHitDie   = 1;
    int weaponHitDie      = 3;
    int critRange         = 0;
    int critMultiplier    = 2;
    int range             = 1;
    mainStat mainStatType = strength;
    friend istream &operator>>(std::istream &input, Weapon &item) {
        string inputString              = "";
        static constexpr char SEPARATOR = ',';
        std::getline(input, inputString, SEPARATOR);
        item.name = inputString;

        std::getline(input, inputString, SEPARATOR);
        item.description = inputString;

        std::getline(input, inputString, SEPARATOR);
        if (inputString == "common") {
            item.rarity = common;
        } else if (inputString == "uncommon") {
            item.rarity = uncommon;
        } else if (inputString == "rare") {
            item.rarity = rare;
        } else if (inputString == "mythic") {
            item.rarity = mythic;
        }
        std::getline(input, inputString, SEPARATOR);
        item.weaponPreHitDie = std::stoi(inputString);

        std::getline(input, inputString, SEPARATOR);
        item.weaponHitDie = std::stoi(inputString);

        std::getline(input, inputString, SEPARATOR);
        item.critRange = std::stoi(inputString);

        std::getline(input, inputString, SEPARATOR);
        item.critMultiplier = std::stoi(inputString);

        std::getline(input, inputString, SEPARATOR);
        item.range = std::stoi(inputString);

        std::getline(input, inputString, SEPARATOR);
        if (inputString == "strengh" || inputString == "1") {
            item.mainStatType = strength;
        } else if (inputString == "agility" || inputString == "2") {
            item.mainStatType = agility;
        } else if (inputString == "intelligence" || inputString == "3") {
            item.mainStatType = intelligence;
        } else {
            item.mainStatType = strength;
        }
        return input;
    }
};

struct Consumable {
    size_t itemID     = 0;
    itemType type     = consumable;
    string name       = "";
    string description = "";
    rarityItem rarity = common;
    int HP            = 0;
    int strength      = 0;
    int dexterity     = 0;
    int luck          = 0;
    int intelligence  = 0;
    int vitality      = 0;
    int duration      = 0; //in seconds
    friend istream &operator>>(std::istream &input, Consumable &item) {
        string inputString              = "";
        static constexpr char SEPARATOR = ',';
        std::getline(input, inputString, SEPARATOR);
        item.name = inputString;

        std::getline(input, inputString, SEPARATOR);
        item.description = inputString;

        std::getline(input, inputString, SEPARATOR);
        if (inputString == "common") {
            item.rarity = common;
        } else if (inputString == "uncommon") {
            item.rarity = uncommon;
        } else if (inputString == "rare") {
            item.rarity = rare;
        } else if (inputString == "mythic") {
            item.rarity = mythic;
        }
        std::getline(input, inputString, SEPARATOR);
        item.HP = std::stoi(inputString);

        std::getline(input, inputString, SEPARATOR);
        item.strength = std::stoi(inputString);

        std::getline(input, inputString, SEPARATOR);
        item.dexterity = std::stoi(inputString);

        std::getline(input, inputString, SEPARATOR);
        item.luck = std::stoi(inputString);

        std::getline(input, inputString, SEPARATOR);
        item.intelligence = std::stoi(inputString);

        std::getline(input, inputString, SEPARATOR);
        item.duration = std::stoi(inputString);

        return input;
    }
};

namespace ItemManager {
    auto getNewID() -> size_t;

    auto ItemManager() -> vector<ItemID> &;

    auto WeaponManager() -> vector<Weapon> &;

    auto ArmorManager() -> vector<Armor> &;

    auto ConsumableManager() -> vector<Consumable> &;
    auto getItem(size_t ID) -> ItemID;

	auto getWeapon(size_t ID) -> Weapon;

	auto getArmor(size_t ID) -> Armor;

	auto getConsumable(size_t ID) -> Consumable;
};

class ItemLoader {
  public:
    ItemLoader()  = default;
    ~ItemLoader() = default;
    void init();

  private:
    void constructWeapon(string item);
    void constructArmor(string item);
    void constructConsumable(string item);
    void constructGenerics();
};
