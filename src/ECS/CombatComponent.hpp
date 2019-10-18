#pragma once

#include "Components.hpp"

/* This will need to handle input to the player */
class CombatComponent : public Component {
  public:
    CombatComponent()  = default;
    ~CombatComponent() = default;
    void init() {}
    void update() {}
    void draw() {}

	auto Attack(Item item, Stat Attack, Stat Defender) -> void {
		
	}
};