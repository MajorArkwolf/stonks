#include "CombatLog.hpp"
/**
 * @brief Returns the combat log static vector
 * @return The static vector of strings containing the combat log text
 */
auto CombatLog::log() -> vector<string> & {
    static vector<string> m_log = {};
    return m_log;
}
