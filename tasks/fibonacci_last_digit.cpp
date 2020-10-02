#include <iostream>

#ifdef DEBUG
#include <gtest/gtest.h>

#include "utils/timer.h"
#endif

namespace {
int get_fibonacci_last_digit_fast(int n) {
    if (n <= 1)
        return n;

    int previous = 0;
    int current  = 1;

    for (int i = 2; i <= n; ++i) {
        int tmp_previous = previous;
        previous = current;
        current = (tmp_previous + current) % 10;
    }

    return current;
}

#ifdef DEBUG
void test_solution() {
    auto timer = Timer();
    ASSERT_EQ(get_fibonacci_last_digit_fast(3), 2);
    ASSERT_LE(timer.elapsed(), 1000);

    timer.restart();
    ASSERT_EQ(get_fibonacci_last_digit_fast(331), 9);
    ASSERT_LE(timer.elapsed(), 1000);

    timer.restart();
    ASSERT_EQ(get_fibonacci_last_digit_fast(327305), 5);
    ASSERT_LE(timer.elapsed(), 1000);
}
#endif
} // namespace

int main(int argc, char* argv[]) {
    if (argc == 1) {
        int n = 0;
        std::cin >> n;

        std::cout << get_fibonacci_last_digit_fast(n) << std::endl;
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
