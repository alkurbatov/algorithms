#include <iostream>
#include <limits>
#include <vector>

#ifdef DEBUG
#include <gtest/gtest.h>
#endif

namespace {
unsigned solution(size_t money) {
    const unsigned coins[3] = { 1, 3, 4 };
    std::vector<unsigned> min_num_coins(money + 1, 0);

    for (size_t m = 1; m <= money; ++m) {
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
    ASSERT_EQ(solution(1), 1);
    ASSERT_EQ(solution(2), 2);
    ASSERT_EQ(solution(3), 1);
    ASSERT_EQ(solution(4), 1);
    ASSERT_EQ(solution(34), 9);
}
#endif
} // namespace

int main(int argc, char* argv[]) {
    if (argc == 1) {
        size_t n;
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
