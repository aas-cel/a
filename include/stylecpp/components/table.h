#pragma once
#include <vector>
#include <string>
#include <memory>
#include <sstream>
#include "../core/component.h"
#include "../accessibility/aria.h"
#include "../animation/animate.h"

namespace stylecpp {

class Table : public Component, public AccessibleComponent {
    std::vector<std::string> headers_;
    std::vector<std::vector<std::string>> rows_;
    Color header_fg_ = Color::White;
    Color header_bg_ = Color::Blue;
    Color cell_fg_ = Color::Default;
    Color cell_bg_ = Color::Default;
    int padding_ = 1;
    int focused_row_ = -1;
    bool animated_ = false;
public:
    Table() { aria()->set("role", "table"); }
    Table& header(const std::vector<std::string>& h) { headers_ = h; return *this; }
    Table& row(const std::vector<std::string>& r) { rows_.push_back(r); return *this; }
    Table& header_color(Color fg, Color bg) { header_fg_ = fg; header_bg_ = bg; return *this; }
    Table& cell_color(Color fg, Color bg) { cell_fg_ = fg; cell_bg_ = bg; return *this; }
    Table& padding(int p) { padding_ = p; return *this; }
    Table& animated(bool a = true) { animated_ = a; return *this; }
    void set_focus(bool f) override { focused_row_ = f && !rows_.empty() ? 0 : -1; }
    bool has_focus() const override { return focused_row_ >= 0; }
    void on_event(const Event& e) override {
        if (e.type == Event::Type::Key && has_focus()) {
            if (e.key == 'j' && focused_row_ + 1 < (int)rows_.size()) ++focused_row_;
            if (e.key == 'k' && focused_row_ > 0) --focused_row_;
        }
        Component::on_event(e);
    }
    std::string render() const override {
        std::ostringstream oss;
        std::vector<size_t> col_widths(headers_.size(), 0);
        for (size_t i = 0; i < headers_.size(); ++i)
            col_widths[i] = headers_[i].size();
        for (const auto& row : rows_)
            for (size_t i = 0; i < row.size(); ++i)
                if (row[i].size() > col_widths[i]) col_widths[i] = row[i].size();
        // Header
        oss << "|";
        for (size_t i = 0; i < headers_.size(); ++i) {
            auto h = std::make_shared<StyledTextRenderable>(headers_[i]);
            h->color(header_fg_).bg(header_bg_).bold().padding(padding_);
            oss << h->render();
            oss << std::string(col_widths[i] - headers_[i].size(), ' ');
            oss << "|";
        }
        oss << "\n";
        // Rows
        for (size_t r = 0; r < rows_.size(); ++r) {
            oss << "|";
            for (size_t i = 0; i < headers_.size(); ++i) {
                std::string cell = (i < rows_[r].size() ? rows_[r][i] : "");
                auto c = std::make_shared<StyledTextRenderable>(cell);
                c->color(cell_fg_).bg(cell_bg_).padding(padding_);
                if ((int)r == focused_row_) c->bg(Color::Yellow);
                oss << c->render();
                oss << std::string(col_widths[i] - cell.size(), ' ');
                oss << "|";
            }
            oss << "\n";
        }
        if (animated_) {
            std::string out = oss.str();
            std::string anim_out;
            animate(400, [&](float progress) {
                anim_out = out;
            });
            return anim_out;
        }
        return oss.str();
    }
};

inline std::shared_ptr<Table> make_table() { return std::make_shared<Table>(); }

} // namespace stylecpp
