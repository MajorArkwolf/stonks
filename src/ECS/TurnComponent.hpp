#pragma once

#include "ECS.hpp"

/* This will need to handle input to the player */
class TurnComponent : public Component {
  public:
    TurnComponent();
    ~TurnComponent();
    void init();
    void update();
    void draw();

    bool checkTurn();
    void startYourTurn();
    void assignAction();
    void endYourTurn();

  private:
    bool turnPhase2 = false;
    bool isTurn     = false;
};
