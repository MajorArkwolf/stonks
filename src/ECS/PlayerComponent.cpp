#include "PlayerComponent.hpp"
#include "Stonk/Engine.hpp"
#include "Akuma/Akuma.hpp"
#include "CombatComponent.hpp"
#include "EnemyComponent.hpp"
#include "EquipmentComponent.hpp"
#include "MoveComponent.hpp"
#include "PositionComponent.hpp"
#include "StairComponent.hpp"
#include "Stonk/OpenGl.hpp"
#include "TurnComponent.hpp"

/**
 * @brief  Defaulted Constructor
 */
PlayerComponent::PlayerComponent() = default;

/**
 * @brief  Defaulted Destructor
 */
PlayerComponent::~PlayerComponent() = default;

/**
 * @brief  Unused
 */
void PlayerComponent::init() {
    this->audiomgr    = &(Stonk::Engine::get().audio);
    this->stepSound = audiomgr->LoadSound("step.ogg");
}

/**
 * @brief  Checks to see if the player has leveled up, sets the direction they are facing and allows them to move
 */
void PlayerComponent::update() {
    if (this->entity->hasComponent<StatComponent>()) {
        this->entity->getComponent<StatComponent>().expCheck();
    }
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

/**
 * @brief  Draws a grid on the floor to show avaliable moves or attacks
 */
void PlayerComponent::draw() {
    if (this->entity->hasComponent<PositionComponent>()) {

        if (this->entity->hasComponent<FloorComponent>()) {

            if (this->entity->hasComponent<TurnComponent>()) {

                if (this->entity->getComponent<TurnComponent>().checkTurn()) {

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
}

/**
 * @brief  sets the facing direction with the buffered direction
 */
void PlayerComponent::setFacing(Facing newFace) {
    facingBuffer = newFace;
}

/**
 * @brief  sets the facing direction into the buffer
 * @param i integerer to be turned into a direction 0 being N and NW being 7
 */
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

/**
 * @brief  sets the facing direction into the buffer
 * @param i integerer to be turned into a direction 0 being N and NW being 7
 */
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

/**
 * @brief  Stops any weird bugs being able to allow a player to issue multiple turns
 */
void PlayerComponent::issueAction() {
    if (this->entity->getComponent<TurnComponent>().checkTurn()) {
        if (!issuedAction) {
            issuedAction = true;
        }
    }
}

/**
 * @brief  Allows the player to skip there turn.
 */
void PlayerComponent::skipTurn() {
    if (this->entity->getComponent<TurnComponent>().checkTurn()) {
        this->entity->getComponent<TurnComponent>().endYourTurn();
    }
}

/**
 * @brief  Allows the program to find out what direction the player is facing
 * @param x unsigned int in the x direction by 1
 * @param y unsigned int in the y direction by 1
 * @return returns a uvec2 coordiante to the square
 */
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

/**
 * @brief  gets the node the current player is looking at
 * @return the Node the player is looking at
 */
Pathing::Node *PlayerComponent::getLookingAtNode() {
    Floor *floor = this->entity->getComponent<FloorComponent>().getFloor();
    Pathing::Node *currentNode =
        this->entity->getComponent<PositionComponent>().getNode();
    auto facingNode = getNodeFacing(currentNode->x, currentNode->y);
    return floor->getGridNode(facingNode);
}

/**
 * @brief  Determines what execution the player had intended to do
 */
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
            this->audiomgr->PlaySound(this->stepSound);
            issuedAction = false;
        }
        issuedAction = false;
    }
}

/**
 * @brief  draws the square around the player
 * @param  size the size of the frame
 * @param  wireframe the thickness of the line
 */
auto PlayerComponent::drawSquare(float size, bool wireframe) -> void {
    drawRectangle(size, size, wireframe);
}

/**
 * @brief  draws a rectangle around the player
 * @param  _width the width of the line
 * @param  _height the height it draws to
 * @param  wireframe outline the square
 */
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
