#include "StairComponent.hpp"
bool StairComponent::checkStairActive() {
    return stairCaseActivate;
}
void StairComponent::SetStairActive() {
    stairCaseActivate = true;
}

void StairComponent::resetStairCase() {
	stairCaseActivate = false;
}