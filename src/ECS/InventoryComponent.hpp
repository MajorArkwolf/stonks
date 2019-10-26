#pragma once

#include "ECS.hpp"
#include <vector>
#include "../Akuma/Items/ItemManager.hpp"

struct Item {
    ItemID mItem;
    size_t quantitiy = 0;
};

/* This will need to handle input to the player */
class InventoryComponent : public Component {
  public: 
    InventoryComponent();
    ~InventoryComponent();
    void init();
    void update();
    void draw();

	void addItemToInventory(ItemID newItem);
    void equipItemtoSlot(ItemID equipItem);
    //ItemID dropItem();
    std::vector<Item> inventoryList;
};
