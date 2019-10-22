#include "ItemManager.hpp"
#include "Stonk/Engine.hpp"
#include <assert.h>

void ItemLoader::init() {
    constructGenerics();
    auto &engine = Stonk::Engine::get();
    string path    = engine.basepath + "res/info/itemList.csv";

    static constexpr char SEPARATOR = ',';
    auto fileinput   = ifstream();
    auto currentLine = string();
    fileinput.open(path);
    string line, item, x;
    if (!fileinput.is_open()) {
        std::cout << "Error Reading itemList.csv file! Make sure its in root!"
                  << std::endl;
	}
    //assert(fileinput.is_open());
	//Removes the header
    std::getline(fileinput, line, '\n');
    std::getline(fileinput, line, '\n');
    std::getline(fileinput, line, '\n');
    while (std::getline(fileinput, line, '\n')) {
        stringstream ss(line);
        std::getline(ss, x, SEPARATOR);
        std::getline(ss, item, '\n');
        if (x == "weapon") {
            constructWeapon(item);
        } else if (x == "armor") {
            constructArmor(item);
        } else if (x == "consumeable") {
            constructConsumable(item);
        }
    }
}

void ItemLoader::constructWeapon(string item) {
    Weapon temp;
    stringstream ss = stringstream(item);
    ss >> temp;

	temp.itemID = ItemManager::getNewID();
	ItemID newID;
    newID.itemID = temp.itemID;
    newID.type   = weapon;
    newID.name   = temp.name;
    newID.description   = temp.description;
    ItemManager::ItemManager().push_back(newID);
    ItemManager::WeaponManager().push_back(temp);

}

void ItemLoader::constructArmor(string item) {
    Armor temp;
    stringstream ss = stringstream(item);
    ss >> temp;

    
	temp.itemID = ItemManager::getNewID();
	ItemID newID;
    newID.itemID = temp.itemID;
    newID.type   = armor;
    newID.name   = temp.name;
    newID.description = temp.description;
    ItemManager::ItemManager().push_back(newID);
    ItemManager::ArmorManager().push_back(temp);
}

void ItemLoader::constructConsumable(string item) {
    Consumable temp;
    stringstream ss = stringstream(item);
    ss >> temp;


	temp.itemID = ItemManager::getNewID();
	ItemID newID;
    newID.itemID = temp.itemID;
    newID.type   = consumable;
    newID.name   = temp.name;
    newID.description = temp.description;
    ItemManager::ItemManager().push_back(newID);
    ItemManager::ConsumableManager().push_back(temp);
}

void ItemLoader::constructGenerics() {
    Weapon fists;
    fists.itemID          = ItemManager::getNewID();
    fists.name            = "Fists";
    fists.description     = "Everybody was kong-fu fighting.";
    fists.weaponPreHitDie = 2;
    fists.weaponHitDie    = 2;
    fists.critRange       = 5;
    fists.critMultiplier  = 2;
    fists.range           = 1;
    fists.mainStatType    = strength;
    ItemID fistID;
    fistID.itemID      = fists.itemID;
    fistID.name        = fists.name;
    fistID.description = fists.description;
    fistID.type        = weapon;
    ItemManager::ItemManager().push_back(fistID);
    ItemManager::WeaponManager().push_back(fists);

	Armor rags;
    rags.itemID           = ItemManager::getNewID();
    rags.name             = "Fists";
    rags.description      = "Everybody was kong-fu fighting.";
    rags.dexPentalty      = 0;
    rags.armorBonus       = 0;

    ItemID firstID;
    firstID.itemID      = rags.itemID;
    firstID.name        = rags.name;
    firstID.description = rags.description;
    firstID.type        = armor;
    ItemManager::ItemManager().push_back(firstID);
    ItemManager::ArmorManager().push_back(rags);
}
