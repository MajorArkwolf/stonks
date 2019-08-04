#include "Workaround.hpp"

#include "Glut.hpp"

/**
 * Applies OS specific GLUT workarounds.
 */
auto applyWorkarounds() -> void {
    /* Workaround for event suppression on macOS. */
#ifdef __APPLE__
    CGSetLocalEventsSuppressionInterval(0.0);
#endif
}
