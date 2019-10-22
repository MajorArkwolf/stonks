#include "ItemManager.hpp"

void ItemLoader::init() {
    auto fileinput   = ifstream();
    auto currentLine = string();
    fileinput.open("itemList.csv");
    string x, item;
    if (!fileinput.is_open()) {
        std::cout << "Read failure" << std::endl;
        return;
    }
    if (x == "weapon") {
        constructWeapon(item);
	} else if (x == "armor") {
        constructArmor(item);
	} else if (x == "consumeable") {
        constructConsumable(item);
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
