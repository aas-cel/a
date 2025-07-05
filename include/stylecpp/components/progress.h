#pragma once
#include <string>
#include <vector>
#include <memory>
#include <sstream>
#include "../core/component.h"

namespace stylecpp {

class ProgressBar : public Component {
    int value_ = 0;
    int max_ = 100;
    Color fg_ = Color::Green;
    Color bg_ = Color::Black;
    bool animated_ = false;
    bool focused_ = false;
public:
    ProgressBar(int value, int max = 100) : value_(value), max_(max) {}
    ProgressBar& color(Color c) { fg_ = c; return *this; }
    ProgressBar& bg(Color c) { bg_ = c; return *this; }
    ProgressBar& animated(bool a) { animated_ = a; return *this; }
    void set_focus(bool f) override { focused_ = f; }
    bool has_focus() const override { return focused_; }
    std::string render() const override {
        int width = 30;
        int filled = (value_ * width) / max_;
        std::ostringstream oss;
        oss << "[";
        for (int i = 0; i < width; ++i) {
            if (i < filled)
                oss << "\033[" << (fg_ == Color::Green ? "32" : "36") << "m#";
            else
                oss << "\033[" << (bg_ == Color::Black ? "30" : "37") << "m-";
        }
        oss << "\033[0m] ";
        oss << value_ << "%";
        if (focused_) oss << " <";
        return oss.str();
    }
};

inline std::shared_ptr<ProgressBar> make_progress(int value, int max = 100) { return std::make_shared<ProgressBar>(value, max); }

} // namespace stylecpp
