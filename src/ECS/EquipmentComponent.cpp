#include "EquipmentComponent.hpp"
#include "InventoryComponent.hpp"
#include "../Akuma/CombatLog.hpp"

EquipmentComponent::EquipmentComponent()  = default;
EquipmentComponent::~EquipmentComponent() = default;
void EquipmentComponent::init() {
    mainHand = ItemManager::getItem(1);
    eArmor   = ItemManager::getItem(2);
}
void EquipmentComponent::update() {}
void EquipmentComponent::draw() {}

void EquipmentComponent::equipMainHand(ItemID item) {
    if (item.type == weapon) {
        if (mainHand.itemID == 1) {
            mainHand = item;
        } else {
            if (unquipMainHand()) {
                mainHand = item;
            } else {
                CombatLog::log().push_back(
                    "Unable to unequip at this point in time.");
            }
        }
    } else {
        CombatLog::log().push_back("You cant equip that here");
    }
}
void EquipmentComponent::equipOffHand(ItemID item) {
    if (item.type == weapon /*add shield here further down the line */) {
        if (offHand.itemID == 0 /*Once implemented 2H this will also need to make sure its not a 2h*/) {
            offHand = item;
        } else {
            if (unequipOffHand()) {
                offHand = item;
            } else {
                CombatLog::log().push_back(
                    "Unable to unequip at this point in time.");
            }
        }
    } else {
        CombatLog::log().push_back("You cant equip that here");
    }
}
void EquipmentComponent::equipTwoHand(ItemID item) {
    if (item.type == weapon) {
        if (mainHand.itemID == 1 && offHand.itemID == 1) {
            mainHand = item;
            offHand  = ItemID();
        } else {
            if (unequipTwoHand()) {
                mainHand = item;
                offHand  = ItemID();
            } else {
                CombatLog::log().push_back(
                    "Unable to unequip at this point in time.");
            }
        }
    } else {
        CombatLog::log().push_back("You cant equip that here");
    }
}
void EquipmentComponent::equipArmor(ItemID item) {
    if (item.type == armor) {
        if (eArmor.itemID == 2) {
            eArmor = item;
        } else {
            if (unequipArmor()) {
                eArmor = item;
                eArmor = item;
            } else {
                CombatLog::log().push_back(
                    "Unable to unequip at this point in time.");
            }
        }
    } else {
        CombatLog::log().push_back("You cant equip that here");
    }
}
bool EquipmentComponent::unquipMainHand() {
    this->entity->getComponent<InventoryComponent>().addItemToInventory(mainHand);
    return true;
}
bool EquipmentComponent::unequipOffHand() {
    this->entity->getComponent<InventoryComponent>().addItemToInventory(offHand);
    return true;
}
bool EquipmentComponent::unequipTwoHand() {
    //this->entity->getComponent<InventoryComponent>().addItemToInventory(tw);
    return true;
}
bool EquipmentComponent::unequipArmor() {
    this->entity->getComponent<InventoryComponent>().addItemToInventory(eArmor);
    return true;
}

ItemID EquipmentComponent::getEquippedMainHand() {
    return mainHand;
}

ItemID EquipmentComponent::getEquippedOffHand() {
    return offHand;
}

ItemID EquipmentComponent::getEquippedArmor() {
    return eArmor;
}
