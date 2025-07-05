#pragma once
#include <thread>
#include <functional>

namespace stylecpp {

inline void run_async(std::function<void()> fn) {
    std::thread(std::move(fn)).detach();
}

inline void sleep_ms(int ms) {
    std::this_thread::sleep_for(std::chrono::milliseconds(ms));
}

} // namespace stylecpp
