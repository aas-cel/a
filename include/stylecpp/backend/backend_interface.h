#pragma once
#include <string>
#include <memory>
#include <functional>
#include <vector>
#include "../core/style.h"

namespace stylecpp {

// Forward declarations
class Component;
struct Event {
    enum class Type { None, Key, Mouse, Focus, Blur, Custom };
    Type type = Type::None;
    int key = 0;
    int mouse_x = 0, mouse_y = 0;
    std::string custom;
};

class BackendInterface {
public:
    virtual ~BackendInterface() = default;
    virtual void render(const std::shared_ptr<Component>& root) = 0;
    virtual void main_loop(const std::shared_ptr<Component>& root) = 0;
    virtual void send_event(const Event& event) = 0;
};

using BackendPtr = std::shared_ptr<BackendInterface>;

} // namespace stylecpp
