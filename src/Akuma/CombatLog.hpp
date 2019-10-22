#pragma once

#include <vector>
#include <string>

using std::string;
using std::vector;

namespace CombatLog {

	static vector<string>& log() {
        static vector<string> m_log = {};
        return m_log;
	}
}
