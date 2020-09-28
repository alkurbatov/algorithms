#include <iostream>
#include <limits>
#include <vector>

#ifdef DEBUG
#include <gtest/gtest.h>
#endif

namespace {
unsigned solution(unsigned money) {
    const unsigned coins[3] = { 1, 3, 4 };
    std::vector<unsigned> min_num_coins(money + 1, 0);

    for (unsigned m = 1; m <= money; ++m) {
        min_num_coins[m] = std::numeric_limits<unsigned>::max();

        for (auto c : coins) {
            if (m < c)
                continue;

            unsigned num_coins = min_num_coins[m - c] + 1;
            if (num_coins < min_num_coins[m])
                min_num_coins[m] = num_coins;
        }
    }

    return min_num_coins.back();
}

#ifdef DEBUG
void test_solution() {
    EXPECT_EQ(solution(1), 1);
    EXPECT_EQ(solution(2), 2);
    EXPECT_EQ(solution(3), 1);
    EXPECT_EQ(solution(4), 1);
    EXPECT_EQ(solution(34), 9);
}
#endif
} // namespace

int main(int argc, char* argv[]) {
    if (argc == 1) {
        unsigned n;
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
