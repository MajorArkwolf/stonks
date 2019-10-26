#pragma once

#include "../Akuma/Floor.hpp"
#include "ECS.hpp"
#include "../Akuma/RNG/Dice.hpp"

/* This will need to handle input to the player */
class EnemyComponent : public Component {
  public:
    enum class Facing { N, NE, E, SE, S, SW, W, NW };
    EnemyComponent();
    ~EnemyComponent();
    void init();
    void update();
    void draw();
    void setFacing(Facing newFace);

    void updateFacing();

    void setFacing(int i);

    void SetPlayerTarget(Entity *currentPlayer);

    void turnEntity(int i);

	auto deadEnemy() -> void;
    bool lockedToPlayer = false;

  private:
    Dice diceroller;
    int turn            = 0;
    Facing facingBuffer = Facing::N;
    Facing facing       = Facing::N;
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
