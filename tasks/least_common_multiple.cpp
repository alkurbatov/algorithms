#include <algorithm>
#include <iostream>

#ifdef DEBUG
#include <gtest/gtest.h>

#include "utils/timer.h"
#endif

namespace {
unsigned gcd_fast(unsigned a, unsigned b) {
    if (b == 0)
        return a;

    if (a < b)
        std::swap(a, b);

    return gcd_fast(b, a % b);
}

long long lcm_fast(long long a, long long b) {
    return (a * b) / gcd_fast(a, b);
}

#ifdef DEBUG
void test_solution() {
    auto timer = Timer();
    ASSERT_EQ(lcm_fast(6, 8), 24);
    ASSERT_LE(timer.elapsed(), 1000);

    timer.restart();
    ASSERT_EQ(lcm_fast(12, 15), 60);
    ASSERT_LE(timer.elapsed(), 1000);

    timer.restart();
    ASSERT_EQ(lcm_fast(761457, 614573), 467970912861);
    ASSERT_LE(timer.elapsed(), 1000);

    timer.restart();
    ASSERT_EQ(lcm_fast(10000000, 9999999), 99999990000000);
    ASSERT_LE(timer.elapsed(), 1000);
}
#endif
} // namespace

int main(int argc, char* argv[]) {
    if (argc == 1) {
        int a, b;
        std::cin >> a >> b;

        std::cout << lcm_fast(a, b) << std::endl;
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
