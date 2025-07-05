#pragma once
#include <string>
#include <sstream>
#include <map>
#include <vector>

namespace stylecpp {

// Minimal JSON serialization for config/settings
inline std::string to_json(const std::map<std::string, std::string>& obj) {
    std::ostringstream oss;
    oss << "{";
    bool first = true;
    for (const auto& [k, v] : obj) {
        if (!first) oss << ", ";
        oss << '"' << k << "": " << '"' << v << '"';
        first = false;
    }
    oss << "}";
    return oss.str();
}

inline std::map<std::string, std::string> from_json(const std::string& json) {
    // Minimal: not robust, for demo/config only
    std::map<std::string, std::string> obj;
    size_t pos = 0;
    while ((pos = json.find('"', pos)) != std::string::npos) {
        size_t key_start = pos + 1;
        size_t key_end = json.find('"', key_start);
        std::string key = json.substr(key_start, key_end - key_start);
        size_t val_start = json.find('"', key_end + 1) + 1;
        size_t val_end = json.find('"', val_start);
        std::string val = json.substr(val_start, val_end - val_start);
        obj[key] = val;
        pos = val_end + 1;
    }
    return obj;
}

} // namespace stylecpp
