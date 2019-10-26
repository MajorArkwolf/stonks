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
    void factorySetup(Floor * currentFloor, Entity * currentPlayer,
                      vector<Entity *> &currentEnemies);
    void generateEnemy(unsigned int floorLevel);
    void generateEnemy(unsigned int floorLevel, unsigned int amount);

  private:
    Floor *floor   = nullptr;
    Entity *player = nullptr;
    vector<Entity> &enemies;
    vector<string> models = {"goblin_baseball.obj", "goblin_warrior_spear.obj",
                             "gobline_warhammer.obj"};
};

