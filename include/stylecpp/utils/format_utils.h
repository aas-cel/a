#pragma once
#include <string>
#include <sstream>
#include <iomanip>

namespace stylecpp {

inline std::string pad_left(const std::string& s, size_t width, char fill = ' ') {
    if (s.size() >= width) return s;
    return std::string(width - s.size(), fill) + s;
}

inline std::string pad_right(const std::string& s, size_t width, char fill = ' ') {
    if (s.size() >= width) return s;
    return s + std::string(width - s.size(), fill);
}

inline std::string to_upper(const std::string& s) {
    std::string out = s;
    for (auto& c : out) c = toupper(c);
    return out;
}

inline std::string to_lower(const std::string& s) {
    std::string out = s;
    for (auto& c : out) c = tolower(c);
    return out;
}

} // namespace stylecpp
