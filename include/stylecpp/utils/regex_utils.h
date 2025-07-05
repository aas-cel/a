#pragma once
#include <string>
#include <regex>
#include <vector>

namespace stylecpp {

inline bool match_regex(const std::string& text, const std::string& pattern) {
    return std::regex_match(text, std::regex(pattern));
}

inline std::vector<std::string> findall_regex(const std::string& text, const std::string& pattern) {
    std::vector<std::string> results;
    std::regex re(pattern);
    auto words_begin = std::sregex_iterator(text.begin(), text.end(), re);
    auto words_end = std::sregex_iterator();
    for (auto it = words_begin; it != words_end; ++it) {
        results.push_back(it->str());
    }
    return results;
}

} // namespace stylecpp
