#include <iostream>
#include <vector>

#ifdef DEBUG
#include <gtest/gtest.h>

#include "utils/timer.h"
#endif

namespace {
int fibonacci_fast(int n) {
    std::vector<int> numbers(n + 1);
    numbers[0] = 0;
    numbers[1] = 1;

    for (int i = 2; i <= n; ++i)
        numbers[i] = numbers[i - 1] + numbers[i - 2];

    return numbers.back();
}

#ifdef DEBUG
void test_solution() {
    Timer timer;
    ASSERT_EQ(fibonacci_fast(3), 2);
    EXPECT_LE(timer.elapsed(), 1000);

    timer.restart();
    ASSERT_EQ(fibonacci_fast(10), 55);
    EXPECT_LE(timer.elapsed(), 1000);
}
#endif
} // namespace

int main(int argc, char* argv[]) {
    if (argc == 1) {
        int n = 0;
        std::cin >> n;

        std::cout << fibonacci_fast(n) << std::endl;
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
