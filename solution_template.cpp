#include <iostream>

#ifdef DEBUG
#include <gtest/gtest.h>

#include "utils/timer.h"
#endif

namespace {
unsigned solution(long long n) {
    return n;
}

#ifdef DEBUG
void test_solution() {
    auto timer = Timer();
    ASSERT_EQ(solution(1), 1);
    EXPECT_LE(timer.elapsed(), 1000);

    timer.restart();
    ASSERT_EQ(solution(2), 2);
    EXPECT_LE(timer.elapsed(), 1000);
}
#endif
} // namespace

int main(int argc, char* argv[]) {
    if (argc == 1) {
        long long n;
        std::cin >> n;

        std::cout << solution(n) << std::endl;
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
