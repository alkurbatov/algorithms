#include <iostream>

#include "timer.h"

Timer::Timer(): m_start(std::chrono::high_resolution_clock::now()) {
}

void Timer::restart() {
    m_start = std::chrono::high_resolution_clock::now();
}

unsigned Timer::elapsed() const {
    return std::chrono::duration_cast<std::chrono::milliseconds>(
        std::chrono::high_resolution_clock::now() - m_start).count();
}
