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
    StatComponent(CharacterSheet newStat) {
        this->stat = newStat;
    }
    ~StatComponent() = default;
    void init() {}
    void update() {}
    void draw() {}

    auto getStrengthMod() {
        return getMod(this->stat.strength);
	}
    auto getIntelligenceMod() {
        return getMod(this->stat.intelligence);
    }
    auto getDexterityMod() {
        return getMod(this->stat.dexterity);
    }
    auto getLuckMod() {
        return getMod(this->stat.luck);
    }
    auto getVitalityMod() {
        return getMod(this->stat.vitality);
    }

    auto getStatSheet() -> CharacterSheet & {
        return stat;
    }

    auto setStatSheet(CharacterSheet newStat) -> void {
        this->stat = newStat;
    }
    CharacterSheet stat;

  private:
    auto getMod(int stat) -> int {
        if (stat <= 1) {
            return -5;
        } else if (stat < 4) {
            return -4;
        } else if (stat < 6) {
            return -3;
        } else if (stat < 8) {
            return -2;
        } else if (stat < 10) {
            return -1;
        } else if (stat < 12) {
            return 0;
        } else if (stat < 14) {
            return 1;
        } else if (stat < 16) {
            return 2;
        } else if (stat < 18) {
            return 3;
        } else if (stat < 20) {
            return 4;
        } else if (stat < 22) {
            return 5;
        } else if (stat < 24) {
            return 6;
        } else if (stat < 26) {
            return 7;
        } else if (stat < 28) {
            return 8;
        } else if (stat < 30) {
            return 9;
        } else if (stat > 30) {
            return 10;
		}
    }
};
