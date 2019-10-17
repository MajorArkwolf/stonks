#pragma once

#include <array>
#include <string>
#include "Components.hpp"

using std::string;

/// This needs to be removed and instead use the Items module.
struct Item {
    size_t itemID   = 0;
    size_t quantity = 0;
    string itemName     = "";
};



class InventoryComponent : public Component {
  public:
    void init() {
        /*start the player with a health potion and a short sword*/
	}
    void update() {
        /*for (size_t i = 0; i <= uniqueItemAmount; i++) {
            if(updateable){
				do something.
			}
			
		}*/
	}
    void draw() {}
    bool addItem(Item item) {
        /// Searches through the current inventory to see if the item exists in the inventory.
        for (size_t i = 0; i <= uniqueItemAmount; ++i) {
            /// If the item is found, it checks the quantity.
            if (inventory[i].itemID == item.itemID) {
                if (inventory[i].quantity < 100) {
                    inventory[i].quantity++;
                    return true;
                } else {
                    /// Returns false if there is already 99 items in the inventory, this means its maxed out.
                    return false;
                }
            }
        }
        /// If the item isnt found then attempt to add to your inventory.
        if (uniqueItemAmount < inventory.max_size()) {
            inventory[uniqueItemAmount + 1] = item;
            uniqueItemAmount++;
        } else {
            /// If the player has 99 unique items then they wont be able to pick up.
            return false;
        }
    }
    Item dropItem(size_t index) {
        /*My idea for this is to create an object called loot bag on the floor
        at the current player position. that will hold items, if there is a
        lootbag at the players feet, it will add the existing loot bag.
        */
        Item temp = inventory[index];
        if (inventory[index].quantity <= 1) {
            ShrinkArray(index);
        }
        inventory[index].quantity -= 1;
		
		return temp;
    }
    bool useItem(size_t listID) {
        auto temp = inventory[listID];
        return true;
    }

	///Used to get rid of invalid objects.
    void ShrinkArray(size_t index) {
        for (auto i = index; index < uniqueItemAmount; i++) {
            inventory[index] = inventory[index + 1];
        }
		///I do not know if this works. :shrug: sandro problem.
        uniqueItemAmount -= 1;
    }

  private:
    size_t uniqueItemAmount = 0;
    std::array<Item, 99> inventory;
};
