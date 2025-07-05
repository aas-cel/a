#pragma once
#include <vector>
#include <string>
#include <memory>
#include "../core/component.h"

namespace stylecpp {

class Menu : public Component {
    std::vector<std::string> items_;
    int selected_ = 0;
public:
    Menu(const std::vector<std::string>& items) : items_(items) {}
    Menu& select(int idx) { if (idx >= 0 && idx < (int)items_.size()) selected_ = idx; return *this; }
    void set_focus(bool f) override { if (!items_.empty()) selected_ = 0; }
    bool has_focus() const override { return true; }
    void on_event(const Event& e) override {
        if (e.type == Event::Type::Key) {
            if (e.key == 'j' && selected_ + 1 < (int)items_.size()) ++selected_;
            if (e.key == 'k' && selected_ > 0) --selected_;
        }
        Component::on_event(e);
    }
    std::string render() const override {
        std::string out;
        for (size_t i = 0; i < items_.size(); ++i) {
            if ((int)i == selected_)
                out += "> " + items_[i] + " <\n";
            else
                out += "  " + items_[i] + "\n";
        }
        return out;
    }
};

inline std::shared_ptr<Menu> make_menu(const std::vector<std::string>& items) { return std::make_shared<Menu>(items); }

} // namespace stylecpp
