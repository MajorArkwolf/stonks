#include "EnemyFactory.hpp"
#include "RNG/Dice.hpp"

EnemyFactory::EnemyFactory(){};
EnemyFactory::~EnemyFactory() = default;
void EnemyFactory::factorySetup(Floor *currentFloor, Entity *currentPlayer) {
    floor = currentFloor;
    player = currentPlayer;
}

void EnemyFactory::generateEnemy(unsigned int floorLevel,
                                 vector<Entity *> &enemies, Manager &manager) {
    Dice diceRoller;
    unsigned int enemyCount = diceRoller.Roll(floorLevel, 3u);
    generateEnemy(floorLevel, enemyCount, enemies, manager);
}

void EnemyFactory::generateEnemy(unsigned int floorLevel, unsigned int amount,
                                 vector<Entity *> &enemies, Manager &manager) {
    Dice diceRoller;

    for (unsigned i = 0; i <= amount; ++i) {
        string modelName = models.at(diceRoller.Roll(1u, (models.size() - 1u)));
        enemies.push_back(&manager.addEntity());
        enemies.at(i)->addComponentID<ScaleComponent>(glm::vec3{0.5, 0.5,
        0.5}); enemies.at(i)->addComponentID<PositionComponent>(); bool
        walkable    = false; auto maxDistance = floor->getGridSize(); glm::vec2
        temp   = {0, 0}; do {
            temp.x = diceRoller.Roll(static_cast<int>(maxDistance.x - 1));
            temp.y = diceRoller.Roll(static_cast<int>(maxDistance.y - 1));
            if (floor->getGridNode(temp)->walkable) {
                enemies.at(i)->getComponent<PositionComponent>().setNode(
                    floor->getGridNode(temp));
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
        enemies.at(i)->getComponent<StatComponent>().stat =
            generateStats(floorLevel);
        string name = "Monster " + std::to_string(i);
        enemies.at(i)->getComponent<StatComponent>().stat.name = name;
        enemies.at(i)->getComponent<StatComponent>().setupEntity();
        enemies.at(i)->addComponentID<TurnComponent>();
    }
	
}

CharacterSheet EnemyFactory::generateStats(unsigned int floorLevel) {
    CharacterSheet result;
    Dice dicerRoller;
    result.dexterity            = 7;
    result.strength             = 7;
    result.vitality             = 7;
    result.luck                 = 7;
    result.intelligence         = 7;
    unsigned int amountOfPoints = dicerRoller.Roll(floorLevel, 3u);
    for (auto e = amountOfPoints; e > 0; e--) {
        auto i = dicerRoller.Roll(1, 5);
        if (i == 1) {
            result.dexterity++;
		} else if (i == 2) {
            result.intelligence++;
		} else if (i == 3) {
            result.strength++;
		} else if (i == 4) {
            result.vitality++;
		} else if (i == 5) {
            result.luck++;
		}
	}
	return result;
}

// void Akuma::generateLevel() {
//}