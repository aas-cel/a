#pragma once
#include <string>
#include <map>
#include <memory>

namespace stylecpp {

class AriaAttributes {
    std::map<std::string, std::string> attrs_;
public:
    void set(const std::string& key, const std::string& value) { attrs_[key] = value; }
    std::string get(const std::string& key) const {
        auto it = attrs_.find(key);
        return it != attrs_.end() ? it->second : "";
    }
    const std::map<std::string, std::string>& all() const { return attrs_; }
};

class AccessibleComponent {
    std::shared_ptr<AriaAttributes> aria_ = std::make_shared<AriaAttributes>();
public:
    std::shared_ptr<AriaAttributes> aria() { return aria_; }
};

} // namespace stylecpp
