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
};

struct Armor {
    size_t itemID     = 0;
    itemType type     = armor;
    string name       = "";
    rarityItem rarity = common;
    int armorBonus    = 0;
    int dexPentalty   = 0;
    istream &operator>>(std::istream &input) {
        static constexpr char SEPARATOR = ',';
	}
};

struct Weapon {
    size_t itemID     = 0;
    itemType type     = weapon;
    string name       = "";
    rarityItem rarity   = common;
    int weaponPreHitDie = 1;
    int weaponHitDie    = 3;
    int critRange       = 0;
    int critMultiplier  = 2;
    istream &operator>>(std::istream &input) {
        string inputString              = "";
        static constexpr char SEPARATOR = ',';
    }
};

struct Consumable {
    size_t itemID     = 0;
    itemType type     = consumable;
    string name       = "";
    rarityItem rarity = common;
    int HP            = 0;
    int strength      = 0;
    int dexterity     = 0;
    int luck          = 0;
    int intelligence  = 0;
    int vitality      = 0;
    int duration      = 0; //in seconds
    istream &operator>>(std::istream &input) {
        static constexpr char SEPARATOR = ',';
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
