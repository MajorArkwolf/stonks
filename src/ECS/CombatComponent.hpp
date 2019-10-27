#pragma once

#include "../Akuma/Pathing/Node.hpp"
#include "ECS.hpp"
#include "Akuma/Items/ItemManager.hpp"
#include "../Akuma/RNG/Dice.hpp"
#include "Stonk/Audio.hpp"



class CombatComponent : public Component {
  public:
    CombatComponent();
    ~CombatComponent();
    void init();
    void update();
    void draw();

    void attackEntity(Entity *opponent);
    int weaponDamage(int weaponPreHitDie, int weaponHitDie);

    int weaponDamage(int weaponPreHitDie, int weaponHitDie,
                     int weaponCritMultiplier);

    void attackEntity(Pathing::Node *opponentSquare);

  private:
    Stonk::Audio *audiomgr = nullptr;
    Stonk::Audio::Sound combatSound;
    Stonk::Audio::Sound naturalCritSound;
    Stonk::Audio::Sound critSound;

    Dice diceroller;
    void singleHanded(Entity *opponent);
    void logInformation(string info);
    void logInformation(int damage, Entity *opponent);
    void logInformation(int damage, Entity *opponent, Weapon weapon);
};
