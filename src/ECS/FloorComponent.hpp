#pragma once

#include "../Akuma/Floor.hpp"
#include "Components.hpp"

/* This will allow entites access to the floor component.
    This may be slow and need to be reworked.
*/
class FloorComponent : public Component {
  public:
    FloorComponent()  = default;
    ~FloorComponent() = default;
    void init() {}
    void update() {}
    void draw() {}
    void setFloor(Floor &newFloor) {
        this->floor = &newFloor;
        floorSet    = true;
    }
    Floor *getFloor() {
        if (floorSet == true) {
            return floor;
        } else {
            return nullptr;
        }
    }

  private:
    bool floorSet = false;
    Floor *floor  = nullptr;
};
