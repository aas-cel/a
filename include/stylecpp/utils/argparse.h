#pragma once
#include <string>
#include <vector>
#include <map>
#include <sstream>

namespace stylecpp {

class ArgParser {
    std::map<std::string, std::string> options_;
public:
    ArgParser(int argc, char** argv) {
        for (int i = 1; i < argc; ++i) {
            std::string arg = argv[i];
            if (arg.rfind("--", 0) == 0 && i + 1 < argc) {
                options_[arg.substr(2)] = argv[++i];
            }
        }
    }
    std::string get(const std::string& key, const std::string& def = "") const {
        auto it = options_.find(key);
        return it != options_.end() ? it->second : def;
    }
    bool has(const std::string& key) const {
        return options_.count(key) > 0;
    }
};

} // namespace stylecpp
