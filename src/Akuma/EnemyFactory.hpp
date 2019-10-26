#pragma once

#include <string>
#include <vector>

#include "../ECS/Components.hpp"
#include "Floor.hpp"

using std::string;
using std::vector;

class EnemyFactory {
  public:
    EnemyFactory();
    ~EnemyFactory();
    void factorySetup(Floor *currentFloor, Entity *currentPlayer);
    void generateEnemy(unsigned int floorLevel, vector<Entity *> &enemies,
                       Manager &manager);
    void generateEnemy(unsigned int floorLevel, unsigned int amount,
                       vector<Entity *> &enemies, Manager &manager);

  private:
    Floor *floor          = nullptr;
    Entity *player        = nullptr;
    vector<string> models = {
        "goblin_baseball.obj",   "goblin_warrior_spear.obj",
        "gobline_warhammer.obj", "ghost.obj",
        "goblin_fighter.obj",    "rock_golem.obj",
        "skeleton_knight.obj"};
    CharacterSheet generateStats(unsigned int floorLevel);
};
