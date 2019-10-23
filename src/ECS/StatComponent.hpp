#pragma once

#include <string>

#include "ECS.hpp"

struct CharacterSheet {
    std::string name = "";
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
    StatComponent();
    StatComponent(CharacterSheet newStat);
    ~StatComponent();
    void init();
    void update();
    void draw();

    auto getStrengthMod() -> int;
    auto getIntelligenceMod() -> int;
    auto getDexterityMod() -> int;
    auto getLuckMod() -> int;
    auto getVitalityMod() -> int;
    auto getStatSheet() -> CharacterSheet &;
    auto setStatSheet(CharacterSheet newStat) -> void;
    CharacterSheet stat;

  private:
    auto getMod(int checkStat) -> int;
};
