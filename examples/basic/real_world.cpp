#include <iostream>
#include "../../include/stylecpp/stylecpp.h"
#include <thread>
#include <memory>

using namespace stylecpp;

// --- Real World: Interactive UI with FTXUI Backend ---
#ifdef STYLECPP_HAS_FTXUI
#include <ftxui/component/screen_interactive.hpp>
#include <ftxui/component/component.hpp>
#include <ftxui/component/component_base.hpp>
using namespace ftxui;

int run_ftxui_demo() {
    std::string input_content;
    int progress_value = 50;
    bool button_clicked = false;
    std::string status_message;
    int selected_row = 0;

    auto input = stylecpp::make_input("Type your name...");
    auto button = stylecpp::make_button("Submit");
    auto progress = stylecpp::make_progress(progress_value);
    auto table = stylecpp::make_table();
    table->header({"Name", "Role", "Status"})
         .row({"Alice", "Admin", "Active"})
         .row({"Bob", "User", "Inactive"})
         .row({"Carol", "Moderator", "Active"});

    // FTXUI interactive components
    Component input_ftxui = Input(&input_content, "Type your name...");
    Component progress_ftxui = Renderer([&] {
        return hbox({
            text("Progress: ") | color(Color::Magenta),
            gauge(progress_value / 100.0f),
            text(" ") + text(std::to_string(progress_value) + "%")
        });
    });
    // --- Extended FTXUI Components ---
    // Spinner animation state
    int spinner_frame = 0;
    Component spinner_ftxui = Renderer([&] {
        static const std::vector<std::string> frames = {"|", "/", "-", "\\", "|", "/", "-", "\\"};
        return text(" ") + text(frames[spinner_frame % frames.size()]) | color(Color::Green);
    });
    // Notification state
    bool show_notification = false;
    std::string notification_message = "Welcome to StyleCPP!";
    Component notification_ftxui = Renderer([&] {
        if (!show_notification) return text("");
        return text(notification_message) | bgcolor(Color::Blue) | color(Color::White) | bold | border;
    });
    // Card info for selected user
    std::vector<std::vector<std::string>> users = {
        {"Alice", "Admin", "Active"},
        {"Bob", "User", "Inactive"},
        {"Carol", "Moderator", "Active"}
    };
    Component card_ftxui = Renderer([&] {
        auto& user = users[selected_row];
        return vbox({
            text("User Card") | bold | color(Color::Cyan),
            text("Name: " + user[0]),
            text("Role: " + user[1]),
            text("Status: " + user[2])
        }) | border | bgcolor(Color::Black) | color(Color::White);
    });
    // Menu for user selection
    int menu_selected = 0;
    std::vector<std::string> menu_entries = {"Alice", "Bob", "Carol"};
    Component menu_ftxui = Menu(&menu_entries, &menu_selected);
    Component menu_action_btn = Button("Select User", [&] {
        selected_row = menu_selected;
        notification_message = "Selected: " + users[selected_row][0];
        show_notification = true;
    });
    Component button_ftxui = Button("Submit", [&] {
        button_clicked = true;
        status_message = "Hello, " + input_content + "!";
        progress_value = std::min(100, progress_value + 10);
        notification_message = "Submitted: " + input_content;
        show_notification = true;
    });
    Component dec_progress = Button("-", [&] { progress_value = std::max(0, progress_value - 5); });
    Component inc_progress = Button("+", [&] { progress_value = std::min(100, progress_value + 5); });
    Component next_row = Button("Next Row", [&] { selected_row = (selected_row + 1) % 3; });
    Component prev_row = Button("Prev Row", [&] { selected_row = (selected_row + 2) % 3; });

    // Add more options: theme switcher, reset, and help
    bool dark_theme = true;
    Component theme_switch = Button("Switch Theme", [&] {
        dark_theme = !dark_theme;
        if (dark_theme) {
            ThemeManager::setTheme({.primary=Color::Cyan, .background=Color::Black, .text=Color::White});
        } else {
            ThemeManager::setTheme({.primary=Color::Blue, .background=Color::White, .text=Color::Black});
        }
    });
    Component reset_btn = Button("Reset", [&] {
        input_content.clear();
        progress_value = 0;
        button_clicked = false;
        status_message.clear();
        selected_row = 0;
        show_notification = false;
    });
    Component help_btn = Button("Help", [&] {
        status_message = "Tab: Next | Shift+Tab: Prev | Enter: Activate | Esc: Reset";
    });

    auto layout = Container::Vertical({
        Renderer([&] { return text("StyleCPP FTXUI Demo") | bold | color(Color::Cyan); }),
        notification_ftxui,
        input_ftxui,
        button_ftxui,
        Renderer([&] { return text(button_clicked ? status_message : "Press Submit") | color(Color::Green); }),
        hbox({dec_progress, progress_ftxui, inc_progress, spinner_ftxui}),
        table_ftxui,
        hbox({prev_row, next_row}),
        hbox({theme_switch, reset_btn, help_btn}),
        Renderer([&] { return text("User Menu:") | color(Color::Yellow); }),
        hbox({menu_ftxui, menu_action_btn}),
        card_ftxui,
        Renderer([&] { return text("Use Tab to navigate, Enter to activate, and type in the input box.") | color(Color::Gray); })
    });
    // Spinner animation timer
    std::thread spinner_thread([&] {
        while (true) {
            std::this_thread::sleep_for(std::chrono::milliseconds(120));
            spinner_frame++;
        }
    });
    spinner_thread.detach();

    auto screen = ScreenInteractive::TerminalOutput();
    return screen.Loop(layout);
}
#endif

int main() {
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

    auto card = make_card();
    card->title("User Profile").content("John Doe\nSoftware Engineer").color(Color::White).bg(Color::Black).padding(2).shadow(true);
    std::cout << card->render() << std::endl;

    auto progress = make_progress(75);
    std::cout << progress->render() << std::endl;

    auto spinner = make_spinner();
    for (int i = 0; i < 8; ++i) {
        std::cout << "\r" << spinner->render() << std::flush;
        std::this_thread::sleep_for(std::chrono::milliseconds(100));
    }
    std::cout << std::endl;

    auto row = make_container();
    auto txt2 = text("Next to button");
    txt2->color(Color::Yellow).padding(1);
    row->add(btn).add(txt2);
    std::cout << row->render() << std::endl;

    // --- Advanced: Table Component ---
    auto table = make_table();
    table->header({"Name", "Role", "Status"})
         .row({"Alice", "Admin", "Active"})
         .row({"Bob", "User", "Inactive"})
         .row({"Carol", "Moderator", "Active"})
         .color(Color::White)
         .bg(Color::Black)
         .border(BorderStyle::Double)
         .padding(1);
    std::cout << table->render() << std::endl;

    // --- Advanced: Runtime Theme Switching ---
    Theme lightTheme = {
        .primary = Color::Blue,
        .secondary = Color::Green,
        .background = Color::White,
        .text = Color::Black,
        .border = Color::Gray
    };
    ThemeManager::setTheme(lightTheme);
    auto txtLight = text("Switched to Light Theme!");
    txtLight->color(lightTheme.primary).bg(lightTheme.background).bold().padding(2).border(BorderStyle::Rounded);
    std::cout << txtLight->render() << std::endl;

    // --- Advanced: Simple Grid Layout ---
    auto grid = make_container();
    auto cell1 = text("Cell 1")->color(Color::Red).padding(1);
    auto cell2 = text("Cell 2")->color(Color::Green).padding(1);
    auto cell3 = text("Cell 3")->color(Color::Blue).padding(1);
    grid->add(cell1).add(cell2).add(cell3);
    std::cout << grid->render() << std::endl;

    std::cout << (Terminal::supportsColors() ? "Terminal supports colors" : "No color support") << std::endl;

#ifdef STYLECPP_HAS_FTXUI
    return run_ftxui_demo();
#else
    return 0;
#endif
}
