#pragma once
#include <chrono>
#include <string>
#include <iomanip>
#include <sstream>

namespace stylecpp {

inline std::string now_time() {
    auto now = std::chrono::system_clock::now();
    std::time_t t = std::chrono::system_clock::to_time_t(now);
    std::tm tm = *std::localtime(&t);
    std::ostringstream oss;
    oss << std::put_time(&tm, "%Y-%m-%d %H:%M:%S");
    return oss.str();
}

} // namespace stylecpp
