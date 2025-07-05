#pragma once
#include "backend_interface.h"
#include "../core/component.h"
#include <memory>

namespace stylecpp {

class FTXUIBackend : public BackendInterface {
public:
    void render(const std::shared_ptr<Component>& root) override;
    void main_loop(const std::shared_ptr<Component>& root) override;
    void send_event(const Event& event) override;
};

using FTXUIBackendPtr = std::shared_ptr<FTXUIBackend>;

} // namespace stylecpp
