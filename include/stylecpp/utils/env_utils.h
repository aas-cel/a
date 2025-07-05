#pragma once
#include <string>
#include <cstdlib>

namespace stylecpp {

inline std::string get_env(const std::string& var) {
    const char* val = std::getenv(var.c_str());
    return val ? std::string(val) : std::string();
}

inline bool is_env_true(const std::string& var) {
    auto v = get_env(var);
    return v == "1" || v == "true" || v == "TRUE";
}

} // namespace stylecpp
