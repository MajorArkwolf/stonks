#pragma once

#include "Components.hpp"

/* This will need to handle input to the player */
class TurnComponent : public Component {
  public:
    TurnComponent()    = default;
    ~TurnComponent() = default;
    void init() {}
    void update() {}
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
