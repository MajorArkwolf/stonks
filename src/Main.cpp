#include <cstddef>

#include "Shay/Shay.hpp"
#include "Stonk/Engine.hpp"
#include "ECS/ECS.hpp"
#include "ECS/Components.hpp"

int main([[maybe_unused]] int argc, [[maybe_unused]] char **argv) {
    Stonk::Engine::run();

    return EXIT_SUCCESS;
}
