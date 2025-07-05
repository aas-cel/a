#pragma once
#include <string>
#include <sstream>
#include <iomanip>
#include "../core/color.h"

namespace stylecpp {

inline std::string color_to_hex(Color c) {
    switch (c) {
        case Color::Black: return "#000000";
        case Color::Red: return "#ff0000";
        case Color::Green: return "#00ff00";
        case Color::Yellow: return "#ffff00";
        case Color::Blue: return "#0000ff";
        case Color::Magenta: return "#ff00ff";
        case Color::Cyan: return "#00ffff";
        case Color::White: return "#ffffff";
        case Color::LightGray: return "#cccccc";
        case Color::DarkGray: return "#333333";
        case Color::LightRed: return "#ff6666";
        case Color::LightGreen: return "#66ff66";
        case Color::LightYellow: return "#ffff99";
        case Color::LightBlue: return "#6699ff";
        case Color::LightMagenta: return "#ff99ff";
        case Color::LightCyan: return "#99ffff";
        default: return "#000000";
    }
}

inline Color hex_to_color(const std::string& hex) {
    // Minimal: only a few colors
    if (hex == "#ff0000") return Color::Red;
    if (hex == "#00ff00") return Color::Green;
    if (hex == "#0000ff") return Color::Blue;
    if (hex == "#ffff00") return Color::Yellow;
    if (hex == "#00ffff") return Color::Cyan;
    if (hex == "#ff00ff") return Color::Magenta;
    if (hex == "#ffffff") return Color::White;
    if (hex == "#000000") return Color::Black;
    return Color::Default;
}

} // namespace stylecpp
