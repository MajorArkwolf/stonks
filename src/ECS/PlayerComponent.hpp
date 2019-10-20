#pragma once

#include "Components.hpp"
/* This will need to handle input to the player */
class PlayerComponent : public Component {
 public:
    enum Facing { N, NE, E, SE, S, SW, W, NW };
    PlayerComponent()  = default;
    ~PlayerComponent() = default;
    void init() {}
    void update() {
        if (this->entity->hasComponent<TurnComponent>()) {
            if (this->entity->getComponent<TurnComponent>().CheckTurn()) {
                facing = facingBuffer;
			}
		}
	}
    void draw() {
        if (this->entity->hasComponent<PositionComponent>()) {
            switch (facing) {
                case N: 
					this->entity->getComponent<PositionComponent>().setRotationN();
					break;
                case NE: 
					this->entity->getComponent<PositionComponent>().setRotationNE();
					break;
                case E: 
					this->entity->getComponent<PositionComponent>().setRotationE();
					break;
                case SE: 
					this->entity->getComponent<PositionComponent>().setRotationSE();
					break;
                case S: 
					this->entity->getComponent<PositionComponent>().setRotationS();
					break;
                case SW: 
					this->entity->getComponent<PositionComponent>().setRotationSW();
					break;
                case W: 
					this->entity->getComponent<PositionComponent>().setRotationW();
					break;
                case NW: 
					this->entity->getComponent<PositionComponent>().setRotationNW();
					break;
                default: 
					this->entity->getComponent<PositionComponent>().setRotationN();
					break;
            }
		}
	}
	void setFacing(Facing newFace) {
        facingBuffer = newFace;
	}

	void setFacing(int i) {
        switch (i) {
            case 0: facingBuffer = N; break;
            case 1: facingBuffer = NE; break;
            case 2: facingBuffer = E; break;
            case 3: facingBuffer = SE; break;
            case 4: facingBuffer = S; break;
            case 5: facingBuffer = SW; break;
            case 6: facingBuffer = W; break;
            case 7: facingBuffer = NW; break;
            default: facingBuffer = N; break;
        }
	}

	void turnEntity(int i) {
        turn += i;
        if (turn > 9) {
            turn -= 9;
        } else if (turn < 0) {
            turn += 9;
		}
        setFacing(turn);
	}

private:
    int turn = 0;
    Facing facingBuffer;
    Facing facing;
};
