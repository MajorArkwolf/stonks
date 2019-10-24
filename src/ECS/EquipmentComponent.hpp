#pragma once

#include "../Akuma/Items/ItemManager.hpp"
#include "ECS.hpp"


/* This will need to handle input to the player */
class EquipmentComponent : public Component {
  public:
    EquipmentComponent();
    ~EquipmentComponent();
    void init();
    void update();
    void draw();

	
    void equipMainHand(ItemID &item);
    void equipOffHand(ItemID &item);
    void equipTwoHand(ItemID &item);
    void equipArmor(ItemID &item);
    bool unquipMainHand();
    bool unequipOffHand();
    bool unequipTwoHand();
    bool unequipArmor();

	ItemID getEquippedMainHand();
    ItemID getEquippedOffHand();
    ItemID getEquippedArmor();

  private:
    ItemID mainHand = ItemID();
    ItemID offHand  = ItemID();
    ItemID eArmor    = ItemID();
};
