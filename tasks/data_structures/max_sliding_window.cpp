#include <deque>
#include <iostream>
#include <vector>

#ifdef DEBUG
#include <gmock/gmock.h>
#include <gtest/gtest.h>

#include "utils/timer.h"
#endif

namespace {
struct Window {
    void slide(unsigned value) {
        while(!m_deque.empty() && m_deque.back() < value)
            m_deque.pop_back();

        m_deque.push_back(value);
    }

    void pop() {
        m_deque.pop_front();
    }

    unsigned max() const {
        return m_deque.front();
    }

 private:
    std::deque<unsigned> m_deque;
};

std::vector<unsigned> solution(const std::vector<unsigned>& A, size_t w) {
    Window window;
    std::vector<unsigned> max;

    for (size_t i = 0; i < w; ++i)
        window.slide(A[i]);
    max.push_back(window.max());

    for (size_t i = w; i < A.size(); ++i) {
        if (window.max() == A[i - w])
            window.pop();

        window.slide(A[i]);
        max.push_back(window.max());
    }

    return max;
}

#ifdef DEBUG
void test_solution() {
    Timer timer;

    ASSERT_THAT(solution({ 2, 7, 3, 1, 5, 2, 6, 2 }, 4), testing::ElementsAre(7, 7, 5, 6, 6));
    EXPECT_LE(timer.elapsed(), 1000);
}
#endif
}  // namespace

int main(int argc, char** argv) {
    if (argc == 1) {
        size_t n;
        std::cin >> n;

        std::vector<unsigned> A(n);
        for (size_t i = 0; i < n; ++i)
            std::cin >> A[i];

        size_t w;
        std::cin >> w;

        std::vector<unsigned> max = solution(A, w);

        for (auto i : max)
            std::cout << i << " ";
        std::cout << std::endl;

        return 0;
    }

#ifdef DEBUG
    if (std::string(argv[1]) == "test") {
        test_solution();
        return 0;
    }
#endif

  return 1;
}
