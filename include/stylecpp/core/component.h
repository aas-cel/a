#pragma once
#include <string>
#include <vector>
#include <memory>
#include <functional>
#include "style.h"
#include "../backend/backend_interface.h"

namespace stylecpp {

class Component : public Renderable, public std::enable_shared_from_this<Component> {
public:
    using Ptr = std::shared_ptr<Component>;
    using EventHandler = std::function<void(const Event&)>;

    virtual ~Component() = default;
    virtual void add(const Ptr&) {}
    virtual void set_focus(bool) {}
    virtual bool has_focus() const { return false; }
    virtual void on_event(const Event& e) { if (event_handler_) event_handler_(e); }
    void set_event_handler(EventHandler h) { event_handler_ = std::move(h); }
    void set_backend(const BackendPtr& backend) { backend_ = backend; }
    BackendPtr backend() const { return backend_; }
protected:
    EventHandler event_handler_;
    BackendPtr backend_;
};

} // namespace stylecpp
