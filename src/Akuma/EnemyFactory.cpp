#include "EnemyFactory.hpp"
#include "RNG/Dice.hpp"

EnemyFactory::EnemyFactory(){};
EnemyFactory::~EnemyFactory() = default;
void EnemyFactory::factorySetup(Floor *currentFloor, Entity *currentPlayer,
                                vector<Entity*> &currentEnemies) {
    floor = currentFloor;
    player = currentPlayer;
    &enemies = &currentEnemies;
}

void EnemyFactory::generateEnemy(unsigned int floorLevel) {
    Dice diceRoller;
    unsigned int enemyCount = diceRoller.Roll(1u, 3u);
    generateEnemy(floorLevel, unsigned int enemyCount);
}

void EnemyFactory::generateEnemy(unsigned int floorLevel, unsigned int amount) {
    Dice diceroller;	

    for (unsigned i = 0; i <= amount; ++i) {
        string modelName = models.at(diceroller.Roll(1u, models.size()));
        enemies.push_back(&manager.addEntity());
        enemies.at(i)->addComponentID<ScaleComponent>(glm::vec3{0.5, 0.5,
        0.5}); enemies.at(i)->addComponentID<PositionComponent>(); bool
        walkable    = false; auto maxDistance = floor.getGridSize(); glm::vec2
        temp   = {0, 0}; do {
            temp.x = diceRoller.Roll(static_cast<int>(maxDistance.x - 1));
            temp.y = diceRoller.Roll(static_cast<int>(maxDistance.y - 1));
            if (floor.getGridNode(temp)->walkable) {
                enemies.at(i)->getComponent<PositionComponent>().setNode(
                    floor.getGridNode(temp));
                walkable = true;
            }
        } while (!walkable);
        enemies.at(i)->addComponentID<ModelComponent>();
        enemies.at(i)->getComponent<ModelComponent>().setModel(modelName);
        enemies.at(i)->addComponentID<MoveComponent>();
        enemies.at(i)->addComponentID<FloorComponent>();
        enemies.at(i)->getComponent<FloorComponent>().setFloor(*floor);
        enemies.at(i)->addComponentID<EnemyComponent>();
        enemies.at(i)->getComponent<EnemyComponent>().SetPlayerTarget(player);
        enemies.at(i)->addComponentID<EquipmentComponent>();
        enemies.at(i)->addComponentID<CombatComponent>();
        enemies.at(i)->addComponentID<StatComponent>();
        string name = "Monster " + std::to_string(i);
        enemies.at(i)->getComponent<StatComponent>().stat.name = name;
        enemies.at(i)->addComponentID<TurnComponent>();
        turnManager.addEntity(enemies.at(i));
    }
	
}

// void Akuma::generateLevel() {
//}