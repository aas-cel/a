#pragma once
#include <string>
#include <filesystem>

namespace stylecpp {

inline std::string join_path(const std::string& a, const std::string& b) {
    return (std::filesystem::path(a) / b).string();
}

inline std::string basename(const std::string& path) {
    return std::filesystem::path(path).filename().string();
}

inline std::string dirname(const std::string& path) {
    return std::filesystem::path(path).parent_path().string();
}

} // namespace stylecpp
