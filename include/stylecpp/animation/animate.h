#pragma once
#include <functional>
#include <chrono>
#include <thread>

namespace stylecpp {

inline void animate(int duration_ms, std::function<void(float)> on_frame) {
    using namespace std::chrono;
    auto start = steady_clock::now();
    int frame_time = 16; // ~60fps
    while (true) {
        auto now = steady_clock::now();
        float t = std::chrono::duration<float, std::milli>(now - start).count() / duration_ms;
        if (t > 1.0f) t = 1.0f;
        on_frame(t);
        if (t >= 1.0f) break;
        std::this_thread::sleep_for(std::chrono::milliseconds(frame_time));
    }
}

} // namespace stylecpp
