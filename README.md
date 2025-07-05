# StyleCPP

A production-quality, utility-first C++ terminal and GUI styling library inspired by TailwindCSS. StyleCPP enables you to build beautiful, interactive, and extensible TUI/GUI applications with a modern, composable API.

## Features
- Utility-first styling: chainable, composable style utilities
- Real components: Button, Input, Card, Table, ProgressBar, Spinner, Container, and more
- Layouts: Container, Grid, Flex, Stack, Responsive
- Theming: runtime theme switching, color palettes, typography
- Backend abstraction: works with ANSI, ncurses, FTXUI, and extensible to ImGui/Qt
- Event system: focus, keyboard, mouse, and custom events
- Terminal detection and compatibility
- Extensible: add your own components, utilities, and backends
- Production-ready: tested, documented, CI/CD, packaging for vcpkg, conan, deb, rpm, conda

## Quick Start

```sh
# Install dependencies (e.g. FTXUI, ncurses, etc.)
# Build the project
cmake -S . -B build
cmake --build build

# Run an example
./build/examples/basic/real_world
```

## Example Usage

```cpp
#include <stylecpp/stylecpp.h>
using namespace stylecpp;

int main() {
    Theme dark = { .primary = Color::Cyan, .background = Color::Black, .text = Color::White };
    ThemeManager::setTheme(dark);
    auto btn = make_button("Click Me").color(dark.text).bg(dark.primary).padding(2);
    std::cout << btn->render() << std::endl;
}
```

## Components
- Button, Input, Card, Table, ProgressBar, Spinner, Container, Grid, Flex, Modal, List, NavigationBar, etc.

## Backends
- Terminal (ANSI), ncurses, FTXUI (TUI/GUI), ImGui/Qt (planned)

## Documentation
- See `docs/` for API, guides, and advanced usage.

## Contributing
Pull requests, issues, and feature requests are welcome! See `CONTRIBUTING.md`.

## License
MIT
