#pragma once
//  Dice.hpp
//  Header file for the dice class
//
//  Peter Crabbe, October 2019

/**
 * @class Dice
 * @brief 	Randomly generates a dice value specified by the user.
 */
class Dice {
  public:
	///Default Constructor set to default
    Dice()  = default;
	///Default Destructor set to default
    ~Dice() = default;
    auto Roll(const int diceNumber, const int diceSided) -> int;
    auto Roll(const int diceSided) -> int;
    auto Roll(const unsigned int diceNumber, const unsigned int diceSided) -> unsigned int;
    auto Roll(const unsigned int diceSided) -> unsigned int;
};
