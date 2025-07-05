#pragma once
#include <string>
#include <memory>
#include "../core/style.h"
#include "../core/component.h"
#include "../accessibility/aria.h"

namespace stylecpp {

class Input : public Component, public AccessibleComponent {
    std::string value_;
    std::string placeholder_;
    Color fg_ = Color::White;
    Color bg_ = Color::Black;
    bool focused_ = false;
    size_t cursor_ = 0;
public:
    explicit Input(const std::string& placeholder = "") : placeholder_(placeholder) {
        aria()->set("role", "textbox");
    }
    Input& value(const std::string& v) { value_ = v; cursor_ = v.size(); return *this; }
    Input& color(Color c) { fg_ = c; return *this; }
    Input& bg(Color c) { bg_ = c; return *this; }
    void set_focus(bool f) override { focused_ = f; }
    bool has_focus() const override { return focused_; }
    std::string render() const override {
        std::string display = value_.empty() ? placeholder_ : value_;
        if (focused_) display.insert(cursor_, "|");
        StyledText t(display);
        t.color(fg_).bg(bg_);
        if (focused_) t.bg(Color::Yellow);
        return t.render();
    }
    void on_event(const Event& e) override {
        if (e.type == Event::Type::Key && focused_) {
            if (e.key == 127 || e.key == 8) { // Backspace
                if (cursor_ > 0) { value_.erase(cursor_-1, 1); --cursor_; }
            } else if (e.key == 330) { // Delete
                if (cursor_ < value_.size()) value_.erase(cursor_, 1);
            } else if (e.key == 260) { // Left
                if (cursor_ > 0) --cursor_;
            } else if (e.key == 261) { // Right
                if (cursor_ < value_.size()) ++cursor_;
            } else if (e.key >= 32 && e.key <= 126) { // Printable
                value_.insert(cursor_, 1, static_cast<char>(e.key)); ++cursor_;
            }
        }
        Component::on_event(e);
    }
};

inline std::shared_ptr<Input> make_input(const std::string& placeholder = "") {
    return std::make_shared<Input>(placeholder);
}

} // namespace stylecpp
