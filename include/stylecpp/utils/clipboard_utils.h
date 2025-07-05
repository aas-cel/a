#pragma once
#include <string>

namespace stylecpp {

// Platform-agnostic clipboard copy (stub for now, real impl per platform)
inline void copy_to_clipboard(const std::string& text) {
    // TODO: Implement for each OS
}

inline std::string paste_from_clipboard() {
    // TODO: Implement for each OS
    return {};
}

} // namespace stylecpp
