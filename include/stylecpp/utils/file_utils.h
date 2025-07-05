#pragma once
#include <string>
#include <fstream>
#include <sstream>

namespace stylecpp {

inline std::string read_file(const std::string& path) {
    std::ifstream f(path);
    std::ostringstream ss;
    ss << f.rdbuf();
    return ss.str();
}

inline void write_file(const std::string& path, const std::string& content) {
    std::ofstream f(path);
    f << content;
}

} // namespace stylecpp
