#include "EquipmentComponent.hpp"
#include "InventoryComponent.hpp"
#include "../Akuma/CombatLog.hpp"

/**
 * @brief  Default Constructor
 */
EquipmentComponent::EquipmentComponent()  = default;

/**
 * @brief  Default Destructor
 */
EquipmentComponent::~EquipmentComponent() = default;

/**
 * @brief  Unused
 */
void EquipmentComponent::init() {
    mainHand = ItemManager::getItem(1);
    eArmor   = ItemManager::getItem(2);
}

/**
 * @brief  Unused
 */
void EquipmentComponent::update() {}

/**
 * @brief  Unused
 */
void EquipmentComponent::draw() {}

/**
 * @brief  Equips item to the main hand
 * @param item the item to be equiped
 */
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

/**
 * @brief  Equips item to the main hand
 * @param item the item to be equiped
 */
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

/**
 * @brief  Equips item to the Two Hand
 * @param item the item to be equiped
 */
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

/**
 * @brief  Equips item to the Armor
 * @param item the item to be equiped
 */
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

/**
 * @brief  Unequips item to the MainHand
 * @return true if it worked
 */
bool EquipmentComponent::unquipMainHand() {
    this->entity->getComponent<InventoryComponent>().addItemToInventory(mainHand);
    return true;
}

/**
 * @brief  Unequips item to the Off Hand
 * @return true if it worked
 */
bool EquipmentComponent::unequipOffHand() {
    this->entity->getComponent<InventoryComponent>().addItemToInventory(offHand);
    return true;
}

/**
 * @brief  Unequips item to the Two Hand
 * @return true if it worked
 */
bool EquipmentComponent::unequipTwoHand() {
    //this->entity->getComponent<InventoryComponent>().addItemToInventory(tw);
    return true;
}

/**
 * @brief  Unequips item to the Armor
 * @return true if it worked
 */
bool EquipmentComponent::unequipArmor() {
    this->entity->getComponent<InventoryComponent>().addItemToInventory(eArmor);
    return true;
}

/**
 * @brief  Get the equiped Main Hand item
 * @return  mainHand the item id
 */
ItemID EquipmentComponent::getEquippedMainHand() {
    return mainHand;
}

/**
 * @brief  Get the equiped Offhand item
 * @return  offHand the item id
 */
ItemID EquipmentComponent::getEquippedOffHand() {
    return offHand;
}

/**
 * @brief  Get the equiped armor item
 * @return  eArmor the item id
 */
ItemID EquipmentComponent::getEquippedArmor() {
    return eArmor;
}
