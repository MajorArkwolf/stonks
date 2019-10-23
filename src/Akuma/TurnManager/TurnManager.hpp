#pragma once
#include <vector>

#include "../../ECS/ECS.hpp"

struct EntityInfo {
	bool operator<(const EntityInfo &actor2) const {
        return this->inititive > actor2.inititive;
	}
    Entity *entity = nullptr;
    int currentDexMod = 0;
    int inititive = 0;
};

class TurnManager {
  public:
    TurnManager()  = default;
    ~TurnManager() = default;
    void update();
    void addEntity(Entity *newEntity);
    void turnOnManager();
    void turnOffManager();
    void sortActors();
    void clearActors();

  private:
    int roundCounter       = 1;
    bool turnManagerSwitch = false;
    bool turnToken         = true;
    std::vector<EntityInfo> actors;
    size_t actorTurnID = 0;
    void checkDexChange();
    
    void giveTokenToEntity(Entity *entity);
    void checkEntityTurnState(Entity *entity);
};
