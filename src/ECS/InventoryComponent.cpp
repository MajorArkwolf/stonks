#include "InventoryComponent.hpp"

#include "Akuma/CombatLog.hpp"
#include "EquipmentComponent.hpp"

InventoryComponent::InventoryComponent()  = default;
InventoryComponent::~InventoryComponent() = default;
void InventoryComponent::init() {}
void InventoryComponent::update() {}
void InventoryComponent::draw() {}

void InventoryComponent::addItemToInventory(ItemID newItem) {
    bool found = false;
    for (auto &i : inventoryList) {
        if (i.mItem.itemID == newItem.itemID) {
            i.quantitiy++;
            found = true;
        }
    }
    if (found == false) {
        Item temp;
        temp.mItem     = newItem;
        temp.quantitiy = 1;
        inventoryList.push_back(temp);
    }
}

void InventoryComponent::equipItemtoSlot(ItemID equipItem) {
    size_t indexOfItem = 0;
	for (const auto &e : inventoryList) {
        if (e.mItem.itemID == equipItem.itemID) {
			break;
		}        
        indexOfItem++;
	}

    if (inventoryList.at(indexOfItem).mItem.type == weapon) {
        this->entity->getComponent<EquipmentComponent>().equipMainHand(
            inventoryList.at(indexOfItem).mItem);
        if (inventoryList.at(indexOfItem).quantitiy > 0) {
            inventoryList.at(indexOfItem).quantitiy--;
        } else {
                inventoryList.at(indexOfItem).quantitiy = 0;
		}
    } else if (inventoryList.at(indexOfItem).mItem.type == armor) {
        this->entity->getComponent<EquipmentComponent>().equipArmor(
            inventoryList.at(indexOfItem).mItem);
        if (inventoryList.at(indexOfItem).quantitiy > 0) {
            inventoryList.at(indexOfItem).quantitiy--;
        } else {
            inventoryList.at(indexOfItem).quantitiy = 0;
        }
    } else {
        CombatLog::log().push_back("You cant equip this.");
    }
    inventoryList.erase(std::remove_if(std::begin(inventoryList),
                                       std::end(inventoryList),
                                       [](const Item &currentItem) {
                                           if (currentItem.quantitiy == 0) {
                                               return true;
                                           }
                                           return false;
                                       }),
                        std::end(inventoryList));
}
// ItemID InventoryComponent::dropItem() {}
