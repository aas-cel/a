#pragma once
#include <string>
#include <iostream>

namespace stylecpp {

inline void clear_screen() {
    std::cout << "\033[2J\033[H";
}

inline void move_cursor(int row, int col) {
    std::cout << "\033[" << row << ";" << col << "H";
}

inline void hide_cursor() {
    std::cout << "\033[?25l";
}

inline void show_cursor() {
    std::cout << "\033[?25h";
}

} // namespace stylecpp
