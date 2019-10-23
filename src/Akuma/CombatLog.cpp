#include "CombatLog.hpp"
auto CombatLog::log() -> vector<string> & {
    static vector<string> m_log = {};
    return m_log;
}
