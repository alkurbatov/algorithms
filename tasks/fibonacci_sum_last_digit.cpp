#include <cstdlib>
#include <iostream>

#ifdef DEBUG
#include <gtest/gtest.h>

#include "utils/timer.h"
#endif

namespace {
unsigned fibonacci_sum_last_digit(long long n) {
    // NOTE(alkurbatov): Pizano period for 10 is 60. See fibonacci_huge.cpp for additional details.
    // As a result, the last digit of F0 + F1 + ... F60 = 0.
    long long rem = n % 60;
    if (rem == 0)
        return 0;

    unsigned previous = 0;
    unsigned current  = 1;
    unsigned sum = 1;

    for (int i = 2; i <= rem; ++i) {
        unsigned tmp_previous = previous;
        previous = current;
        current = (tmp_previous + current) % 10;
        sum = (sum + current) % 10;
    }

    return sum;
}

#ifdef DEBUG
void test_solution() {
    auto timer = Timer();
    ASSERT_EQ(fibonacci_sum_last_digit(0), 0);
    ASSERT_LE(timer.elapsed(), 1000);

    timer.restart();
    ASSERT_EQ(fibonacci_sum_last_digit(1), 1);
    ASSERT_LE(timer.elapsed(), 1000);

    timer.restart();
    ASSERT_EQ(fibonacci_sum_last_digit(3), 4);
    ASSERT_LE(timer.elapsed(), 1000);

    timer.restart();
    ASSERT_EQ(fibonacci_sum_last_digit(100), 5);
    ASSERT_LE(timer.elapsed(), 1000);

    timer.restart();
    ASSERT_EQ(fibonacci_sum_last_digit(240), 0);
    ASSERT_LE(timer.elapsed(), 1000);

    timer.restart();
    ASSERT_EQ(fibonacci_sum_last_digit(832564823476), 3);
    ASSERT_LE(timer.elapsed(), 1000);

    timer.restart();
    ASSERT_EQ(fibonacci_sum_last_digit(614162383528), 9);
    ASSERT_LE(timer.elapsed(), 1000);
}
#endif
} // namespace

int main(int argc, char* argv[]) {
    if (argc == 1) {
        long long n = 0;
        std::cin >> n;

        std::cout << fibonacci_sum_last_digit(n) << std::endl;
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
