#pragma once

namespace Stonk {
    /**
     * @class Viewport
     * @brief Used to hold the default viewport values
     */
    class Viewport {
      private:
        double fov    = 60.0;
        double aspect = 0.0;
        double near   = 0.1;
        double far    = 1000.0;
    };
}
