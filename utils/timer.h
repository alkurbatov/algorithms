#pragma once

#include <chrono>

struct Timer {
    Timer();

    void restart();

    // Returns count of microseconds passed since
    // object creation or the last restart call.
    unsigned elapsed() const;

 private:
    std::chrono::time_point<std::chrono::high_resolution_clock> m_start;
};
