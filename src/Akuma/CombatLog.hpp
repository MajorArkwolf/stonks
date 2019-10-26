#pragma once

#include <string>
#include <vector>

using std::string;
using std::vector;
/**
 * @namespace CombatLog
 * @brief Namespace used to contain the vector of strings that combat logs are sent to
 */
namespace CombatLog {
    auto log() -> vector<string> &;
}
