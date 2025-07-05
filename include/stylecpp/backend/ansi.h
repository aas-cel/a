#pragma once
#include <cstdio>

namespace stylecpp {

class Terminal {
public:
    static bool supportsColors() {
        const char* term = getenv("TERM");
        if (!term) return false;
        return std::string(term).find("color") != std::string::npos;
    }
};

} // namespace stylecpp
