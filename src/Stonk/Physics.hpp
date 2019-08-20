#pragma once

#include <memory>
#include <vector>

#include "Stonk/Entity.hpp"

namespace Stonk {
    /**
     * @brief Stores the game physics state.
     */
    struct State {
        using Entities = std::vector<Entity>;

        Entities entities = Entities{};
    };

    class Physics {
      public:
        auto update(State &state, double dt) -> void;
    };
};

auto operator*(const Stonk::State &rhs, float scalar) -> Stonk::State;
auto operator*(const Stonk::State &rhs, double scalar) -> Stonk::State;
auto operator+(const Stonk::State &lhs, const Stonk::State &rhs) -> Stonk::State;
