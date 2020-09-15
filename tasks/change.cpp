#include <iostream>

#ifdef DEBUG
#include <gtest/gtest.h>

#include "utils/timer.h"
#endif

namespace {
unsigned get_change(unsigned m) {
    unsigned count_of_coins = 0;

    std::div_t res = std::div(m, 10);
    count_of_coins += res.quot;

    res = std::div(res.rem, 5);
    count_of_coins += res.quot;
    count_of_coins += res.rem;

    return count_of_coins;
}

#ifdef DEBUG
void test_solution() {
    auto timer = Timer();
    EXPECT_EQ(get_change(2), 2);
    ASSERT_LE(timer.elapsed(), 1000);

    timer.restart();
    EXPECT_EQ(get_change(28), 6);
    ASSERT_LE(timer.elapsed(), 1000);
}
#endif
} // namespace

int main(int argc, char* argv[]) {
    if (argc == 1) {
        unsigned m;
        std::cin >> m;

        std::cout << get_change(m) << std::endl;
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
