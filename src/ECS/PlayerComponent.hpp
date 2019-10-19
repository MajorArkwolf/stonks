#pragma once

#include "Components.hpp"

/* This will need to handle input to the player */
class PlayerComponent : public Component {
 public:
    PlayerComponent()  = default;
    ~PlayerComponent() = default;
    void init() {}
    void update() {
	}
    void draw() {}
	void isYourTurn() {
        isTurn = true;
	}
	bool endYourTurn() {
        isTurn = false;
        return true;
	}

private:
    bool isTurn = false;
};
