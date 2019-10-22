#pragma once

#include "ECS.hpp"
#include "../Akuma/Pathing/Node.hpp"

/* This will need to handle input to the player */
class CombatComponent : public Component {
  public:
    CombatComponent() = default;
    ~CombatComponent() = default;
    void init() {}
    void update() {}
    void draw() {}

	void attackEntity(Entity *opponent) {

	}

	void attackEntity(Pathing::Node opponentSquare) {

	}

  private:
    Entity *opponent = nullptr;
    bool turnToken                 = false;
};
