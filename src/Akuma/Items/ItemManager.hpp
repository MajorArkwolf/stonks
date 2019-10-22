#pragma once
#include <string>
#include <vector>
#include <sstream>
#include <fstream>
#include <iostream>

using std::ifstream;
using std::stringstream;
using std::istream;

using std::string;
using std::vector;

enum itemType { consumable, armor, weapon, empty };
enum rarityItem { common, uncommon, rare, mythic };

struct ItemID {
    size_t itemID = 0;
    itemType type = empty;
    string name   = "";
    string description = "";
};

struct Armor {
    size_t itemID     = 0;
    itemType type     = armor;
    string name       = "";
    string description = "";
    rarityItem rarity = common;
    int armorBonus    = 0;
    int dexPentalty   = 0;
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
    size_t itemID     = 0;
    itemType type     = weapon;
    string name       = "";
    string description  = "";
    rarityItem rarity   = common;
    int weaponPreHitDie = 1;
    int weaponHitDie    = 3;
    int critRange       = 0;
    int critMultiplier  = 2;
    int range           = 1;
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
    friend istream &operator>>(std::istream &input, Consumable &consumable1) {
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
    static auto getNewID() -> size_t {
        static size_t lastID = 1;
        return lastID++;
    }

    static auto ItemManager() -> vector<ItemID> & {
        static vector<ItemID> itemList = {};
        return itemList;
    }

    static auto WeaponManager() -> vector<Weapon> & {
        static vector<Weapon> weaponList = {};
        return weaponList;
    }

    static auto ArmorManager() -> vector<Armor> & {
        static vector<Armor> armorList = {};
        return armorList;
    }

    static auto ConsumableManager() -> vector<Consumable> & {
        static vector<Consumable> consumableList = {};
        return consumableList;
    }
};

class ItemLoader {
  public:
    ItemLoader()  = default;
    ~ItemLoader() = default;
    void init();
    void constructWeapon(string item);
    void constructArmor(string item);
    void constructConsumable(string item);
};
