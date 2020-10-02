#include <algorithm>
#include <iostream>

#ifdef DEBUG
#include <gtest/gtest.h>

#include "utils/timer.h"
#endif

/* Example of Euclidian algorithm:
357 and 234

357 % 234 = 123

234 % 123 = 111

123 % 111 = 12

111 % 12 = 3

12 % 3 = 0
*/

namespace {
unsigned gcd_fast(unsigned a, unsigned b) {
    if (b == 0)
        return a;

    if (a < b)
        std::swap(a, b);

    return gcd_fast(b, a % b);
}

#ifdef DEBUG
void test_solution() {
    auto timer = Timer();
    ASSERT_EQ(gcd_fast(19, 12), 1);
    ASSERT_LE(timer.elapsed(), 1000);

    timer.restart();
    ASSERT_EQ(gcd_fast(18, 35), 1);
    ASSERT_LE(timer.elapsed(), 1000);

    timer.restart();
    ASSERT_EQ(gcd_fast(357, 234), 3);
    ASSERT_LE(timer.elapsed(), 1000);

    timer.restart();
    ASSERT_EQ(gcd_fast(1653264, 3918848), 61232);
    ASSERT_LE(timer.elapsed(), 1000);
}
#endif
} // namespace

int main(int argc, char* argv[]) {
    if (argc == 1) {
        unsigned a, b;
        std::cin >> a >> b;

        std::cout << gcd_fast(a, b) << std::endl;
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
