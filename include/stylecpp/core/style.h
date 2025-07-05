#pragma once
#include <string>
#include <sstream>
#include <vector>
#include <iostream>
#include <utility>
#include <memory>

namespace stylecpp {

// Color enum for foreground/background
enum class Color {
    Default, Black, Red, Green, Yellow, Blue, Magenta, Cyan, White,
    LightGray, DarkGray, LightRed, LightGreen, LightYellow, LightBlue, LightMagenta, LightCyan
};

// Border style
enum class BorderStyle {
    None, Square, Rounded
};

class Renderable {
public:
    virtual ~Renderable() = default;
    virtual std::string render() const = 0;
};

class StyledText {
    std::string text_;
    Color fg_ = Color::Default;
    Color bg_ = Color::Default;
    bool bold_ = false;
    int padding_ = 0;
    BorderStyle border_ = BorderStyle::None;

    static std::string color_code(Color c, bool bg = false) {
        switch (c) {
            case Color::Default: return bg ? "\033[49m" : "\033[39m";
            case Color::Black: return bg ? "\033[40m" : "\033[30m";
            case Color::Red: return bg ? "\033[41m" : "\033[31m";
            case Color::Green: return bg ? "\033[42m" : "\033[32m";
            case Color::Yellow: return bg ? "\033[43m" : "\033[33m";
            case Color::Blue: return bg ? "\033[44m" : "\033[34m";
            case Color::Magenta: return bg ? "\033[45m" : "\033[35m";
            case Color::Cyan: return bg ? "\033[46m" : "\033[36m";
            case Color::White: return bg ? "\033[47m" : "\033[37m";
            case Color::LightGray: return bg ? "\033[47m" : "\033[37;1m";
            case Color::DarkGray: return bg ? "\033[100m" : "\033[90m";
            case Color::LightRed: return bg ? "\033[101m" : "\033[91m";
            case Color::LightGreen: return bg ? "\033[102m" : "\033[92m";
            case Color::LightYellow: return bg ? "\033[103m" : "\033[93m";
            case Color::LightBlue: return bg ? "\033[104m" : "\033[94m";
            case Color::LightMagenta: return bg ? "\033[105m" : "\033[95m";
            case Color::LightCyan: return bg ? "\033[106m" : "\033[96m";
        }
        return "";
    }

    static std::string border_char(BorderStyle style, bool top, bool left) {
        if (style == BorderStyle::Rounded) {
            if (top && left) return "╭";
            if (top && !left) return "╮";
            if (!top && left) return "╰";
            if (!top && !left) return "╯";
        } else if (style == BorderStyle::Square) {
            if (top && left) return "+";
            if (top && !left) return "+";
            if (!top && left) return "+";
            if (!top && !left) return "+";
        }
        return "";
    }

public:
    explicit StyledText(std::string t) : text_(std::move(t)) {}

    StyledText& color(Color c) { fg_ = c; return *this; }
    StyledText& bg(Color c) { bg_ = c; return *this; }
    StyledText& bold() { bold_ = true; return *this; }
    StyledText& padding(int p) { padding_ = p; return *this; }
    StyledText& border(BorderStyle b) { border_ = b; return *this; }

    std::string render() const {
        std::ostringstream oss;
        std::string pad(padding_, ' ');
        std::string content = pad + text_ + pad;
        if (border_ != BorderStyle::None) {
            std::string top = border_ == BorderStyle::Rounded ? "╭" : "+";
            std::string bottom = border_ == BorderStyle::Rounded ? "╰" : "+";
            std::string hor = border_ == BorderStyle::Rounded ? "─" : "-";
            std::string vert = border_ == BorderStyle::Rounded ? "│" : "|";
            oss << top << std::string(content.size(), hor[0]) << (border_ == BorderStyle::Rounded ? "╮\n" : "+\n");
            oss << vert << content << vert << "\n";
            oss << bottom << std::string(content.size(), hor[0]) << (border_ == BorderStyle::Rounded ? "╯" : "+");
        } else {
            oss << content;
        }
        std::string result = oss.str();
        std::ostringstream final;
        final << color_code(bg_, true) << color_code(fg_, false);
        if (bold_) final << "\033[1m";
        final << result << "\033[0m";
        return final.str();
    }
};

class StyledTextRenderable : public Renderable, public std::enable_shared_from_this<StyledTextRenderable> {
    StyledText styled_;
public:
    explicit StyledTextRenderable(const std::string& t) : styled_(t) {}
    StyledTextRenderable& color(Color c) { styled_.color(c); return *this; }
    StyledTextRenderable& bg(Color c) { styled_.bg(c); return *this; }
    StyledTextRenderable& bold() { styled_.bold(); return *this; }
    StyledTextRenderable& padding(int p) { styled_.padding(p); return *this; }
    StyledTextRenderable& border(BorderStyle b) { styled_.border(b); return *this; }
    std::string render() const override { return styled_.render(); }
    std::shared_ptr<StyledTextRenderable> ptr() { return std::static_pointer_cast<StyledTextRenderable>(shared_from_this()); }
};

inline std::shared_ptr<StyledTextRenderable> text(const std::string& t) { return std::make_shared<StyledTextRenderable>(t); }

} // namespace stylecpp
