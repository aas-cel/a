#pragma once
#include <string>
#include <vector>
#include <memory>
#include "../core/style.h"
#include "../core/component.h"
#include "../accessibility/aria.h"
#include "../animation/animate.h"

namespace stylecpp {

class Button : public Component, public AccessibleComponent {
    std::string label_;
    Color fg_ = Color::White;
    Color bg_ = Color::Blue;
    bool bold_ = true;
    int padding_ = 1;
    BorderStyle border_ = BorderStyle::Rounded;
    bool focused_ = false;
    bool animated_ = false;
public:
    explicit Button(const std::string& label) : label_(label) {
        aria()->set("role", "button");
    }
    Button& color(Color c) { fg_ = c; return *this; }
    Button& bg(Color c) { bg_ = c; return *this; }
    Button& bold(bool b = true) { bold_ = b; return *this; }
    Button& padding(int p) { padding_ = p; return *this; }
    Button& border(BorderStyle b) { border_ = b; return *this; }
    Button& animated(bool a = true) { animated_ = a; return *this; }
    void set_focus(bool f) override { focused_ = f; }
    bool has_focus() const override { return focused_; }
    std::string render() const override {
        StyledText t(label_);
        t.color(fg_).bg(bg_).padding(padding_).border(border_);
        if (bold_) t.bold();
        if (focused_) t.bg(Color::Yellow);
        if (animated_) {
            std::string out;
            animate(300, [&](float progress) {
                out = t.render();
            });
            return out;
        }
        return t.render();
    }
};

inline std::shared_ptr<Button> make_button(const std::string& label) {
    return std::make_shared<Button>(label);
}

} // namespace stylecpp
