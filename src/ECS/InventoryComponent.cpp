#include "InventoryComponent.hpp"

InventoryComponent::InventoryComponent() = default;
InventoryComponent::~InventoryComponent() = default;
void InventoryComponent::init() {}
void InventoryComponent::update() {}
void InventoryComponent::draw() {}

void InventoryComponent::addItemToInventory(ItemID newItem) {
    for (auto &i : inventoryList) {
        if (i.mItem.itemID == newItem.itemID) {
            i.quantitiy++;
            return;
		}
	}
    Item temp;
    temp.mItem = newItem;
    temp.quantitiy = 1;
    inventoryList.push_back(temp);
}
//ItemID InventoryComponent::dropItem() {}
