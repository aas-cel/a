#pragma once
#include <string>
#include <memory>
#include "../core/component.h"

namespace stylecpp {

class Notification : public Component {
    std::string message_;
    Color fg_ = Color::White;
    Color bg_ = Color::Red;
    int duration_ms_ = 2000;
public:
    Notification(const std::string& msg) : message_(msg) {}
    Notification& color(Color c) { fg_ = c; return *this; }
    Notification& bg(Color c) { bg_ = c; return *this; }
    Notification& duration(int ms) { duration_ms_ = ms; return *this; }
    std::string render() const override {
        StyledText t(message_);
        t.color(fg_).bg(bg_).bold().padding(2);
        return t.render();
    }
    int duration() const { return duration_ms_; }
};

inline std::shared_ptr<Notification> make_notification(const std::string& msg) { return std::make_shared<Notification>(msg); }

} // namespace stylecpp
