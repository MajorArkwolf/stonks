#pragma once

#include "Stonk/Camera.hpp"
#include "Stonk/Entity.hpp"

namespace Stonk {
    /**
     * @brief Stonk player subsystem.
     */
    class Player {
        Camera camera;
        auto moveUpDown() -> void;
        // auto jump() -> void;
        auto moveLeftRight() -> void;
        auto moveForwardBack() -> void;
        auto setPosition() -> void;
    };
};
