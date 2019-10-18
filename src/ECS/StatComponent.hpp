#pragma once

#include "Components.hpp"

struct CharacterSheet {
    string name      = "";
    int level        = 1;
    int HD           = 8;
    bool assignedHP  = false;
    int HP           = 1;
    int strength     = 10;
    int dexterity    = 10;
    int luck         = 10;
    int intelligence = 10;
    int vitality     = 10;
};

class StatComponent : public Component {
  public:
    StatComponent() = default;
    StatComponent(CharacterSheet stat) {}
    ~StatComponent() = default;
    void init() {}
    void update() {}
    void draw() {}

    auto setStat(CharacterSheet newStat) -> void {
        stat = newStat;
    }

    CharacterSheet stat;
    
};
