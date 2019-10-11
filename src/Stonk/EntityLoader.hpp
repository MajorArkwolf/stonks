#pragma once
#include <string>

using std::string;

struct EntityStats {
    string name    = "";
    string faction = "";
    string AI      = "";
    string model   = "";
    string texture;
    int HP             = 1;
    int strength       = 10;
    int dexterity      = 10;
    int luck           = 10;
    int intelligence   = 10;
    string armor       = "";
    int armorStats     = 0;
    string shield      = "";
    int shieldStats    = 0;
    string nameWeapon1 = "";
    int weapon1        = 0;
    string nameWeapon2 = "";
    int weapon2        = 0;
    string nameWeapon3 = "";
    int weapon3        = 0;
    string nameWeapon4 = "";
    int weapon4        = 0;
};

class EntityLoader {
  public:
    EntityLoader()  = default;
    ~EntityLoader() = default;
    void LoadEntity(string filename);
    EntityStats entity;
};
