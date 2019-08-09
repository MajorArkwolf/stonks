#pragma once

#include <memory>
#include <vector>

#include "Stonk/Entity.hpp"

/**
 * @brief Stores the game physics state.
 */
struct State {
    using Entities = std::vector<Entity>;

    Entities entities = Entities{};
};

auto operator*(const State &rhs, double scalar) -> State;
auto operator+(const State &lhs, const State &rhs) -> State;

class Physics {
  public:
    auto update(State &state, double dt) -> void;
};
