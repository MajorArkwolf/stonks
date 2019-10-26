#pragma once

#include <vector>
#include <string>
#include "Floor.hpp"
#include "../ECS/Components.hpp"

using std::vector;
using std::string;

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
    Floor *floor   = nullptr;
    Entity *player = nullptr;
    vector<string> models = {"goblin_baseball.obj", "goblin_warrior_spear.obj",
                             "gobline_warhammer.obj"};
    CharacterSheet generateStats(unsigned int floorLevel);
};

