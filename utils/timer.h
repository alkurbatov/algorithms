#pragma once

#include <chrono>

struct Timer {
    Timer();

    void restart();

    unsigned elapsed() const;

 private:
    std::chrono::time_point<std::chrono::high_resolution_clock> m_start;
};
