#pragma once
#include <string>

using std::string;

struct Weapon {
    enum class Base { STRENGTH, DEXTERITY, INTELLIGENCE, LUCK };

    string weaponName   = "Fists";
    int range           = 1;
    int weaponPre       = 1;
    int WeaponPost      = 4;
    int weaponCritRange = 20;
    int weaponCritMod   = 2;
    Base BaseMod        = Base::STRENGTH;
};

struct EntityStats {
    string name      = "";
    int level        = 1;
    int HD           = 8;
    string faction   = "";
    string AI        = "";
    string model     = "";
    string texture   = "";
    bool assignedHP  = false;
    int HP           = 1;
    int strength     = 10;
    int dexterity    = 10;
    int luck         = 10;
    int intelligence = 10;
    int vitality     = 10;
    int armorID      = 0;
    string shield    = "";
    int shieldStats  = 0;
    int weapon1ID;
    int weapon2ID;
};

class EntityLoader {
  public:
    EntityLoader()  = default;
    ~EntityLoader() = default;
    auto LoadEntity(string filename) -> void;
    EntityStats entity;

  private:
    string path = "entities/";
    auto CheckStats() -> void;
    auto GetMod(int stat) -> int;
};
