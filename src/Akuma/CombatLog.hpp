#pragma once

#include <string>
#include <vector>

using std::string;
using std::vector;

namespace CombatLog {
    auto log() -> vector<string> &;
}
