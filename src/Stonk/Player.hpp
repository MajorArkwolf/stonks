#pragma once

#include "Stonk/Entity.hpp"
#include "Stonk/Camera.hpp"

namespace Stonk {
    /**
     * @brief Stonk player subsystem.
     */
    class Player {
        Camera camera;
        auto moveUpDown() -> void;
        //auto jump() -> void;
        auto moveLeftRight() -> void;
        auto moveForwardBack() -> void;
        auto setPosition() -> void;
    };
};
