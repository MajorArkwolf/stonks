#pragma once

#include "Components.hpp"

struct Equiped {
    size_t armorID  = 0;
    size_t weaponID = 0;
};

class EquipmentComponent : public Component {
  private:
    Equiped equipment;

  public:
    EquipmentComponent()  = default;
    ~EquipmentComponent() = default;
    void init() {}
    void update() {}
    void draw() {}

    auto equipArmor(size_t newArmorID) -> bool {
        if (armorID = 0) {
            armorID = newArmorID;
        }
    }
    auto equipWeapon(size_t newWeaponID) -> bool {
        if (weaponID = 0) {
            weaponID = newWeaponID;
        }
        
    }
    auto unequipArmor(size_t entityID) -> bool {
        // attempt to add item back into inventory.
        this->equipment.armorID = 0;
    }
    auto unequipWeapon(size_t entityID) -> bool {
        // attempt to add item back into inventory.
        this->equipment.weaponID = 0;
    }
};
