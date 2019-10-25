#pragma once

#include "ECS.hpp"
#include <vector>
#include "..//Akuma/Items/ItemManager"

struct Item {
    ItemID itemID;
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

	void addItemToInventory();
    //ItemID dropItem();

  private:
	//std::vector<ItemID> inventoryList;
};
