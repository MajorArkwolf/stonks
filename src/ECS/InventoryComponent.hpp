#pragma once

#include <array>

#include "Components.h"
#include "SDL.h"

struct Item {};

using InventoryList = std::array<Item>;

class InventoryComponent : public Component {
  public:
    void init() {}
    void update() {}
    void draw() {}
    bool addItem() {
        if (inventory.size != inventory.max_size) {
        } else {
            return false;
        }
        
    }
    void dropItem() {}
    void useItem() {}

  private:
    InventoryList inventory[99];
};
