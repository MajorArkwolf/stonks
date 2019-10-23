#pragma once

#include <glm/vec2.hpp>
#include <glm/vec3.hpp>

#include "../Akuma/Floor.hpp"
#include "../Akuma/Pathing/Pathfinding.hpp"
#include "../Akuma/RNG/Dice.hpp"
#include "ECS.hpp"
#include "PositionComponent.hpp"
#include "StatComponent.hpp"
#include "TurnComponent.hpp"

/* This will need to handle input to the player */
class EnemyComponent : public Component {
  public:
    enum class Facing { N, NE, E, SE, S, SW, W, NW };
    EnemyComponent()  = default;
    ~EnemyComponent() = default;
    void init();
    void update();
    void draw();
    void setFacing(Facing newFace);

    void updateFacing();

    void setFacing(int i);

    void SetPlayerTarget(Entity *currentPlayer);

    void turnEntity(int i);

  private:
    Dice diceroller;
    int turn            = 0;
    Facing facingBuffer = Facing::N;
    Facing facing       = Facing::N;
    bool lockedToPlayer = false;
    Entity *player      = nullptr;

    // This function is scuffed and wont face the player all the time, cant debug
    // as I dont have enough data to see what the entities are actually doing.
    void determineFacingDirection(Pathing::Node *nextNode);

    auto setTurnAngle() -> void;

    void detectPlayer();

    auto DistanceBetween() -> unsigned int;

    auto goToPlayer() -> void;

    auto moveAction() -> void;
    auto combatCheck() -> void;
};
