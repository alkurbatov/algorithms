#include <iostream>

#ifdef DEBUG
#include <gtest/gtest.h>

#include "utils/timer.h"
#endif

namespace {
unsigned pisano_period(long long m) {
    unsigned previous = 0;
    unsigned current  = 1;

    int i = 1;
    while (true) {
        unsigned tmp_previous = previous;
        previous = current;
        current = (tmp_previous + current) % m;

        if (previous == 0 && current == 1)
            break;

        ++i;
    }

    return i;
}

unsigned fibonacchi_modulo(long long n, long long m) {
    if (n <= 1)
        return n;

    unsigned previous = 0;
    unsigned current  = 1;

    for (int i = 2; i <= n; ++i) {
        unsigned tmp_previous = previous;
        previous = current;
        current = (tmp_previous + current) % m;
    }

    return current;
}

unsigned fibonacci_huge(long long n, long long m) {
    if (n <= 1)
        return n;

    long long rem = n % pisano_period(m);
    return fibonacchi_modulo(rem, m);
}

#ifdef DEBUG
void test_solution() {
    ASSERT_EQ(pisano_period(2), 3);
    ASSERT_EQ(pisano_period(10), 60);
    ASSERT_EQ(pisano_period(13), 28);
    ASSERT_EQ(pisano_period(97), 196);
    ASSERT_EQ(pisano_period(133), 144);
    ASSERT_EQ(pisano_period(144), 24);
    ASSERT_EQ(pisano_period(1000), 1500);

    Timer timer;
    ASSERT_EQ(fibonacci_huge(2015, 3), 1);
    EXPECT_LE(timer.elapsed(), 1000);

    timer.restart();
    ASSERT_EQ(fibonacci_huge(239, 1000), 161);
    EXPECT_LE(timer.elapsed(), 1000);

    timer.restart();
    ASSERT_EQ(fibonacci_huge(9999999999999, 2), 0);
    EXPECT_LE(timer.elapsed(), 1000);

    timer.restart();
    ASSERT_EQ(fibonacci_huge(9999999999999, 1000), 626);
    EXPECT_LE(timer.elapsed(), 1000);

    timer.restart();
    ASSERT_EQ(fibonacci_huge(2816213588, 239), 151);
    EXPECT_LE(timer.elapsed(), 1000);
}
#endif
} // namespace

int main(int argc, char* argv[]) {
    if (argc == 1) {
        long long n, m;
        std::cin >> n >> m;

        std::cout << fibonacci_huge(n, m) << std::endl;
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
