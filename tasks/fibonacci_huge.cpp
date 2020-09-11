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
    while(true) {
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
    EXPECT_EQ(pisano_period(2), 3);
    EXPECT_EQ(pisano_period(13), 28);
    EXPECT_EQ(pisano_period(97), 196);
    EXPECT_EQ(pisano_period(133), 144);
    EXPECT_EQ(pisano_period(144), 24);
    EXPECT_EQ(pisano_period(1000), 1500);

    auto timer = Timer();
    EXPECT_EQ(fibonacci_huge(2015, 3), 1);
    ASSERT_LE(timer.elapsed(), 1000);

    timer.restart();
    EXPECT_EQ(fibonacci_huge(239, 1000), 161);
    ASSERT_LE(timer.elapsed(), 1000);

    timer.restart();
    EXPECT_EQ(fibonacci_huge(9999999999999, 2), 0);
    ASSERT_LE(timer.elapsed(), 1000);

    timer.restart();
    EXPECT_EQ(fibonacci_huge(9999999999999, 1000), 626);
    ASSERT_LE(timer.elapsed(), 1000);

    timer.restart();
    EXPECT_EQ(fibonacci_huge(2816213588, 239), 151);
    ASSERT_LE(timer.elapsed(), 1000);
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
