#pragma once
#include <vector>

#include "../../ECS/ECS.hpp"

struct EntityInfo {
    Entity *entity = nullptr;
    int inititive = 0;
};

class TurnManager {
  public:
    TurnManager()  = default;
    ~TurnManager() = default;
    void update();
    void addEntity(Entity *newEntity);
    void sortActors();
    void giveTokenToEntity(Entity *entity);
    void checkEntityTurnState(Entity *entity);

  private:
    bool turnManagerSwitch = false;
    bool turnToken         = true;
    std::vector<EntityInfo> actors;
    size_t actorTurnID = 0;
};
