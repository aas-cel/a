#ifndef STYLECPP_CONTAINER_H
#define STYLECPP_CONTAINER_H
#include <vector>
#include <string>
#include <memory>
#include <sstream>
#include "../core/component.h"

namespace stylecpp {

class Container : public Component {
    std::vector<Ptr> children_;
    int gap_ = 0;
    int focused_index_ = -1;
public:
    Container& add(const Ptr& child) {
        children_.push_back(child);
        return *this;
    }
    Container& gap(int g) { gap_ = g; return *this; }
    void set_focus(bool f) override {
        if (f && !children_.empty()) {
            focused_index_ = 0;
            children_[0]->set_focus(true);
        } else {
            for (auto& c : children_) c->set_focus(false);
            focused_index_ = -1;
        }
    }
    bool has_focus() const override { return focused_index_ >= 0; }
    void on_event(const Event& e) override {
        if (focused_index_ >= 0 && focused_index_ < (int)children_.size())
            children_[focused_index_]->on_event(e);
        Component::on_event(e);
    }
    std::string render() const override {
        std::ostringstream oss;
        for (size_t i = 0; i < children_.size(); ++i) {
            oss << children_[i]->render();
            if (i + 1 < children_.size())
                oss << std::string(gap_, ' ');
        }
        return oss.str();
    }
};

inline std::shared_ptr<Container> make_container() { return std::make_shared<Container>(); }

} // namespace stylecpp
#endif // STYLECPP_CONTAINER_H
