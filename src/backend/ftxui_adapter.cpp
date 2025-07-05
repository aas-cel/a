// FTXUI library adapter for StyleCPP
#include "../../include/stylecpp/backend/ftxui.h"
#ifdef STYLECPP_HAS_FTXUI
#include <ftxui/component/screen_interactive.hpp>
#include <ftxui/component/component.hpp>
#include <ftxui/component/component_base.hpp>
#include <ftxui/dom/elements.hpp>
using namespace ftxui;
#endif
#include <memory>
#include <iostream>

namespace stylecpp {

#ifdef STYLECPP_HAS_FTXUI
namespace {
Element RenderComponent(const std::shared_ptr<Component>& comp) {
    // Example: Render as text for now; extend for real component tree
    return text(comp->render());
}
}
#endif

void FTXUIBackend::render(const std::shared_ptr<Component>& root) {
#ifdef STYLECPP_HAS_FTXUI
    auto screen = ScreenInteractive::TerminalOutput();
    auto renderer = Renderer([&] { return RenderComponent(root); });
    screen.Loop(renderer);
#else
    std::cout << root->render() << std::endl;
#endif
}

void FTXUIBackend::main_loop(const std::shared_ptr<Component>& root) {
    render(root); // For now, just render; extend for real event loop
}

void FTXUIBackend::send_event(const Event& event) {
    // Real implementation: route event to focused component
}

} // namespace stylecpp
