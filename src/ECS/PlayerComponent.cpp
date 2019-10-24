#include "PlayerComponent.hpp"
#include "StairComponent.hpp"
#include "EnemyComponent.hpp"
#include "MoveComponent.hpp"
#include "PositionComponent.hpp"
#include "TurnComponent.hpp"
#include "CombatComponent.hpp"
#include "EquipmentComponent.hpp"

#include "Akuma/Akuma.hpp"
#include "Stonk/OpenGl.hpp"

PlayerComponent::PlayerComponent() {};
PlayerComponent::~PlayerComponent() = default;
void PlayerComponent::init() {}
void PlayerComponent::update() {
    if (this->entity->hasComponent<TurnComponent>()) {
        if (this->entity->getComponent<TurnComponent>().checkTurn()) {
            facing = facingBuffer;
        }
        if (this->entity->hasComponent<PositionComponent>()) {
            switch (facing) {
                case Facing::N:
                    this->entity->getComponent<PositionComponent>().setRotationN();
                    break;
                case Facing::NE:
                    this->entity->getComponent<PositionComponent>().setRotationNE();
                    break;
                case Facing::E:
                    this->entity->getComponent<PositionComponent>().setRotationE();
                    break;
                case Facing::SE:
                    this->entity->getComponent<PositionComponent>().setRotationSE();
                    break;
                case Facing::S:
                    this->entity->getComponent<PositionComponent>().setRotationS();
                    break;
                case Facing::SW:
                    this->entity->getComponent<PositionComponent>().setRotationSW();
                    break;
                case Facing::W:
                    this->entity->getComponent<PositionComponent>().setRotationW();
                    break;
                case Facing::NW:
                    this->entity->getComponent<PositionComponent>().setRotationNW();
                    break;
            }
        }
        commandExecution();
    }
}
void PlayerComponent::draw() {
    if (this->entity->hasComponent<PositionComponent>()) {

        if (this->entity->hasComponent<FloorComponent>()) {

            if (this->entity->hasComponent<TurnComponent>()) {

                Floor *floor =
                    this->entity->getComponent<FloorComponent>().getFloor();
                Pathing::Node *currentNode =
                    this->entity->getComponent<PositionComponent>().getNode();
                auto gridSize = floor->getGridSize();
                std::vector<Pathing::Node *> playerSurroundings =
                    floor->getNeighbours(*currentNode);
                auto facingNode = getLookingAtNode();

                glLineWidth(3);
                glPushMatrix();
                glTranslatef(gridSize.x / 2, 0, (gridSize.y / 2));
                for (auto n : playerSurroundings) {
                    if (n->walkable) {

                        glPushMatrix();
                        glTranslatef(n->x - 0.5f * gridSize.x, 0,
                                     (n->y - 0.5f * gridSize.y));
                        glPushMatrix();
                        glTranslatef(0.f, 0.04f, 0.f);
                        glEnable(GL_COLOR_MATERIAL);
                        if (facingNode == n) {
                            glTranslatef(0.f, 0.02f, 0.f);
                            glColor3f(1.f, 1.f, 0.f);
                        } else if (n->occupant != nullptr) {
                            if (n->occupant->hasComponent<EnemyComponent>()) {
                                glTranslatef(0.f, 0.01f, 0.f);
                                glColor3f(1, 0, 0);
                            }
                        } else {
                            glColor3f(0, 1, 0);
                        }

                        drawSquare(1, 1);
                        glColor3f(1, 1, 1);
                        glDisable(GL_COLOR_MATERIAL);
                        glPopMatrix();

                        glPopMatrix();
                    }
                }
                glPopMatrix();
                glLineWidth(1);
            }
        }
    }
}
void PlayerComponent::setFacing(Facing newFace) {
    facingBuffer = newFace;
}

void PlayerComponent::setFacing(int i) {
    switch (i) {
        case 0: {
            facingBuffer = Facing::N;
            break;
        }
        case 1: {
            facingBuffer = Facing::NE;
            break;
        }
        case 2: {
            facingBuffer = Facing::E;
            break;
        }
        case 3: {
            facingBuffer = Facing::SE;
            break;
        }
        case 4: {
            facingBuffer = Facing::S;
            break;
        }
        case 5: {
            facingBuffer = Facing::SW;
            break;
        }
        case 6: {
            facingBuffer = Facing::W;
            break;
        }
        case 7: {
            facingBuffer = Facing::NW;
            break;
        }
        default: {
            facingBuffer = Facing::N;
            break;
        }
    }
}

void PlayerComponent::turnEntity(int i) {
    if (this->entity->getComponent<TurnComponent>().checkTurn()) {
        if (turn + i > 7) {
            turn = 0;
        } else if (turn + i < 0) {
            turn = 7;
        } else {
            turn += i;
        }
        setFacing(turn);
    }
}

void PlayerComponent::issueAction() {
    if (this->entity->getComponent<TurnComponent>().checkTurn()) {
        if (!issuedAction) {
            issuedAction = true;
        }
    }
}
void PlayerComponent::skipTurn() {
    if (this->entity->getComponent<TurnComponent>().checkTurn()) {
        this->entity->getComponent<TurnComponent>().endYourTurn();
    }
}

glm::uvec2 PlayerComponent::getNodeFacing(unsigned int x, unsigned int y) {
    glm::uvec2 newNode = {x, y};
    switch (turn) {
        case 0: {
            newNode.y++;
            break;
        }
        case 1: {
            newNode.x++;
            newNode.y++;
            break;
        }
        case 2: {
            newNode.x++;
            break;
        }
        case 3: {
            newNode.x++;
            newNode.y--;
            break;
        }
        case 4: {
            newNode.y--;
            break;
        }
        case 5: {
            newNode.x--;
            newNode.y--;
            break;
        }
        case 6: {
            newNode.x--;
            break;
        }
        case 7: {
            newNode.x--;
            newNode.y++;
            break;
        }
        default: {
            newNode.y++;
            break;
        }
    }
    return newNode;
}

Pathing::Node *PlayerComponent::getLookingAtNode() {
    Floor *floor = this->entity->getComponent<FloorComponent>().getFloor();
    Pathing::Node *currentNode =
        this->entity->getComponent<PositionComponent>().getNode();
    auto facingNode = getNodeFacing(currentNode->x, currentNode->y);
    return floor->getGridNode(facingNode);
}

void PlayerComponent::commandExecution() {
    if (issuedAction) {
        auto newNode = getLookingAtNode();
        if (newNode->occupied) {
            if (newNode->occupant->hasComponent<EnemyComponent>()) {
                issuedAction = false;
				this->entity->getComponent<CombatComponent>().attackEntity(
					newNode->occupant);
            } else if (newNode->occupant->hasComponent<StairComponent>()) {
                newNode->occupant->getComponent<StairComponent>().SetStairActive();
			}
        } else if (newNode->walkable) {
            this->entity->getComponent<MoveComponent>().moveEntityToNode(newNode);
            issuedAction = false;
        }
        issuedAction = false;
    }
}
auto PlayerComponent::drawSquare(float size, bool wireframe) -> void {
    drawRectangle(size, size, wireframe);
}
auto PlayerComponent::drawRectangle(float _width, float _height, bool wireframe)
    -> void {
    if (wireframe) {
        glBegin(GL_LINE_LOOP);
    } else {
        glBegin(GL_POLYGON);
    }
    glVertex3f(-0.5f * _width, 0, 0.5f * _height);
    glVertex3f(0.5f * _width, 0, 0.5f * _height);
    glVertex3f(0.5f * _width, 0, -0.5f * _height);
    glVertex3f(-0.5f * _width, 0, -0.5f * _height);
    glEnd();
}
