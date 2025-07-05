#pragma once
#include <string>
#include <vector>
#include <memory>
#include <sstream>
#include "../core/style.h"
#include "../core/component.h"
#include "../accessibility/aria.h"
#include "../animation/animate.h"

namespace stylecpp {

class Card : public Component, public AccessibleComponent {
    std::string title_;
    std::string content_;
    Color fg_ = Color::White;
    Color bg_ = Color::Black;
    Color border_ = Color::LightGray;
    int padding_ = 1;
    bool shadow_ = false;
    bool focused_ = false;
    bool animated_ = false;
public:
    Card() { aria()->set("role", "region"); }
    Card& title(const std::string& t) { title_ = t; return *this; }
    Card& content(const std::string& c) { content_ = c; return *this; }
    Card& color(Color c) { fg_ = c; return *this; }
    Card& bg(Color c) { bg_ = c; return *this; }
    Card& border(Color c) { border_ = c; return *this; }
    Card& padding(int p) { padding_ = p; return *this; }
    Card& shadow(bool s) { shadow_ = s; return *this; }
    Card& animated(bool a = true) { animated_ = a; return *this; }
    void set_focus(bool f) override { focused_ = f; }
    bool has_focus() const override { return focused_; }
    std::string render() const override {
        std::ostringstream oss;
        StyledTextRenderable titleR(title_);
        titleR.bold().color(fg_).bg(bg_).padding(padding_).border(BorderStyle::Rounded);
        if (focused_) titleR.bg(Color::Yellow);
        StyledTextRenderable contentR(content_);
        contentR.color(fg_).bg(bg_).padding(padding_);
        if (animated_) {
            std::string out;
            animate(400, [&](float progress) {
                out = titleR.render() + "\n" + contentR.render();
            });
            oss << out;
        } else {
            oss << titleR.render() << "\n" << contentR.render();
        }
        if (shadow_) oss << "\n\033[90m" << std::string(title_.size() + 2 * padding_ + 2, ' ') << "\u2595\033[0m";
        return oss.str();
    }
};

inline std::shared_ptr<Card> make_card() { return std::make_shared<Card>(); }

} // namespace stylecpp
