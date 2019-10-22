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

    bool CheckTurn() {
        return this->isTurn;
    }
    void startYourTurn() {
        this->isTurn     = true;
        this->turnPhase2 = true;
    }
    bool endYourTurn() {
        this->isTurn = false;
        this->turnPhase2 = false;
        return true;
    }

  private:
    bool turnPhase2 = false;
    bool isTurn = false;
};
