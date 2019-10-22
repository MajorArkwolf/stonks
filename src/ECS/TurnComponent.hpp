#pragma once

#include "ECS.hpp"

/* This will need to handle input to the player */
class TurnComponent : public Component {
  public:
    TurnComponent()  = default;
    ~TurnComponent() = default;
    void init() {}
    void update() {}
    void draw() {}

    bool checkTurn() {
        return this->turnPhase2;
    }
    void startYourTurn() {
        this->isTurn     = true;
        this->turnPhase2 = true;
    }
	void assignAction() {
        this->isTurn = false;
	}
    void endYourTurn() {
        this->isTurn = false;
        this->turnPhase2 = false;
    }

  private:
    bool turnPhase2 = false;
    bool isTurn = false;
};
