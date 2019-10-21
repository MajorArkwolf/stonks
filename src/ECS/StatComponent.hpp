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
    auto getMod(int checkStat) -> int {
        if (checkStat <= 1) {
            return -5;
        } else if (checkStat < 4) {
            return -4;
        } else if (checkStat < 6) {
            return -3;
        } else if (checkStat < 8) {
            return -2;
        } else if (checkStat < 10) {
            return -1;
        } else if (checkStat < 12) {
            return 0;
        } else if (checkStat < 14) {
            return 1;
        } else if (checkStat < 16) {
            return 2;
        } else if (checkStat < 18) {
            return 3;
        } else if (checkStat < 20) {
            return 4;
        } else if (checkStat < 22) {
            return 5;
        } else if (checkStat < 24) {
            return 6;
        } else if (checkStat < 26) {
            return 7;
        } else if (checkStat < 28) {
            return 8;
        } else if (checkStat < 30) {
            return 9;
        } else if (checkStat > 30) {
            return 10;
        } else {
            return 0;
		}
    }
};
