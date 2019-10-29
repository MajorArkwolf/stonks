#pragma once

#include "../Akuma/Floor.hpp"
#include "ECS.hpp"

/* This will allow entites access to the floor component.
    This may be slow and need to be reworked.
*/
class FloorComponent : public Component {
  public:
    FloorComponent();
    ~FloorComponent();
    void init();
    void update();
    void draw();
    void setFloor(Floor &newFloor);
    Floor *getFloor();

  private:
    bool floorSet = false;
    Floor *floor  = nullptr;
};
