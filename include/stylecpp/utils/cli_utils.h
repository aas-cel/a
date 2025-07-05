#pragma once
#include <string>
#include <vector>
#include <sstream>

namespace stylecpp {

inline std::vector<std::string> split_args(const std::string& cmd) {
    std::istringstream iss(cmd);
    std::vector<std::string> args;
    std::string arg;
    while (iss >> std::quoted(arg)) args.push_back(arg);
    return args;
}

inline void print_help() {
    std::cout << "StyleCPP CLI Usage:\n"
              << "  --help         Show this help message\n"
              << "  --theme THEME  Set theme (dark, light)\n"
              << "  --version      Print version info\n";
}

} // namespace stylecpp
