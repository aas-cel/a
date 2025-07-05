#pragma once
#include "../core/style.h"

namespace stylecpp {

struct Theme {
    Color primary = Color::Blue;
    Color secondary = Color::Cyan;
    Color background = Color::Black;
    Color text = Color::White;
    Color border = Color::LightGray;
};

class ThemeManager {
    static Theme current_;
public:
    static void setTheme(const Theme& t) { current_ = t; }
    static const Theme& getTheme() { return current_; }
};

inline Theme ThemeManager::current_ = Theme{};

} // namespace stylecpp
