#include <iostream>
#include "../../include/stylecpp/stylecpp.h"
#include <memory>

using namespace stylecpp;

int main() {
    // Set a custom theme
    Theme darkTheme = {
        .primary = Color::Cyan,
        .secondary = Color::Magenta,
        .background = Color::Black,
        .text = Color::White,
        .border = Color::LightGray
    };
    ThemeManager::setTheme(darkTheme);

    auto txt = text("Hello, StyleCPP!");
    txt->color(darkTheme.primary).bg(darkTheme.background).bold().padding(2).border(BorderStyle::Rounded);
    std::cout << txt->render() << std::endl;

    auto btn = make_button("Click Me");
    btn->color(darkTheme.text).bg(darkTheme.primary).padding(2).border(BorderStyle::Rounded);
    std::cout << btn->render() << std::endl;

    auto row = make_container();
    auto txt2 = text("Next to button");
    txt2->color(Color::Yellow).padding(1);
    row->add(btn).add(txt2);
    std::cout << row->render() << std::endl;

    std::cout << (Terminal::supportsColors() ? "Terminal supports colors" : "No color support") << std::endl;
    return 0;
}
