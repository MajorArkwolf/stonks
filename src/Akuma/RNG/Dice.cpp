#include "Dice.hpp"

#include <random>
/**
 * @brief  Rolls X amount of dice with X sides
 *
 * @param diceNumber Number of dice to roll
 * @param diceSided Number of sides on the dice
 * @return Returns running total of dice rolled
 */
auto Dice::Roll(const int diceNumber, const int diceSided) -> int {
    auto runningTotal = int();
    std::random_device rd;
    std::mt19937 mt(rd());
    std::uniform_int_distribution<int> dist(1, diceSided);
    for (auto i = 0; i < diceNumber; ++i) {
        runningTotal += dist(mt);
    }
    return runningTotal;
}

/**
 * @brief  Rolls 1 dice with X sides
 *
 * @param diceSided Number of sides on the dice
 * @return Returns running total of dice rolled
 */
auto Dice::Roll(const int diceSided) -> int {
    return Roll(1, diceSided);
}
/**
 * @brief  Rolls X amount of dice with X sides
 *
 * @param diceNumber Number of dice to roll
 * @param diceSided Number of sides on the dice
 * @return Returns running total of dice rolled
 */
auto Dice::Roll(const unsigned int diceNumber, const unsigned int diceSided) -> unsigned int {
    auto runningTotal = 0u;
    std::random_device rd;
    std::mt19937 mt(rd());
    std::uniform_int_distribution<unsigned int> dist(1u, diceSided);
    for (auto i = 0u; i < diceNumber; ++i) {
        runningTotal += dist(mt);
    }
    return runningTotal;
}

/**
 * @brief  Rolls 1 dice with X sides
 *
 * @param diceSided Number of sides on the dice
 * @return Returns running total of dice rolled
 */
auto Dice::Roll(const unsigned int diceSided) -> unsigned int {
    return Roll(1u, diceSided);
}
