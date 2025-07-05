#pragma once
#include <string>
#include <vector>
#include <memory>
#include <chrono>
#include <thread>
#include <sstream>
#include "../core/component.h"

namespace stylecpp {

class Spinner : public Component {
    std::vector<std::string> frames_ = {"|", "/", "-", "\\"};
    Color color_ = Color::Cyan;
    int speed_ms_ = 100;
    mutable int frame_ = 0;
    bool focused_ = false;
public:
    Spinner() = default;
    Spinner& color(Color c) { color_ = c; return *this; }
    Spinner& speed(int ms) { speed_ms_ = ms; return *this; }
    void set_focus(bool f) override { focused_ = f; }
    bool has_focus() const override { return focused_; }
    std::string render() const override {
        std::ostringstream oss;
        oss << "\033[" << (color_ == Color::Cyan ? "36" : "37") << "m" << frames_[frame_ % frames_.size()] << "\033[0m";
        frame_ = (frame_ + 1) % frames_.size();
        std::this_thread::sleep_for(std::chrono::milliseconds(speed_ms_));
        if (focused_) oss << " <";
        return oss.str();
    }
};

inline std::shared_ptr<Spinner> make_spinner() { return std::make_shared<Spinner>(); }

} // namespace stylecpp
