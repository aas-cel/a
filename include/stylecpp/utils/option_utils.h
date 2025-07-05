#pragma once
#include <string>
#include <vector>
#include <map>

namespace stylecpp {

struct Option {
    std::string name;
    std::string description;
    std::string default_value;
};

class OptionSet {
    std::vector<Option> options_;
    std::map<std::string, std::string> values_;
public:
    void add(const Option& opt) { options_.push_back(opt); values_[opt.name] = opt.default_value; }
    void set(const std::string& name, const std::string& value) { values_[name] = value; }
    std::string get(const std::string& name) const {
        auto it = values_.find(name);
        return it != values_.end() ? it->second : "";
    }
    const std::vector<Option>& options() const { return options_; }
};

} // namespace stylecpp
