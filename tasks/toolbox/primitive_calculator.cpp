#include <algorithm>
#include <iostream>
#include <limits>
#include <vector>

#ifdef DEBUG
#include <gmock/gmock.h>
#include <gtest/gtest.h>

#include "utils/timer.h"
#endif

namespace {
void solution(size_t n, std::vector<unsigned>* sequence) {
    const unsigned multipliers[2] = { 2, 3 };
    std::vector<unsigned> min_num_steps(n + 1, 0);

    for (size_t i = 1; i <= n; ++i) {
        min_num_steps[i] = min_num_steps[i - 1] + 1;

        for (auto m : multipliers) {
            if (i % m)
                continue;

            unsigned num_steps = min_num_steps[i / m] + 1;
            if (num_steps < min_num_steps[i])
                min_num_steps[i] = num_steps;
        }
    }

    while (n >= 1) {
        sequence->push_back(n);

        unsigned next_n = 0;
        unsigned steps_count = std::numeric_limits<unsigned>::max();

        if (n % 3 == 0 && min_num_steps[n / 3] < steps_count) {
            next_n = n / 3;
            steps_count = min_num_steps[next_n];
        }

        if (n % 2 == 0 && min_num_steps[n / 2] < steps_count) {
            next_n = n / 2;
            steps_count = min_num_steps[next_n];
        }

        if (min_num_steps[n - 1] < steps_count)
            next_n = n - 1;

        n = next_n;
    }

    std::reverse(sequence->begin(), sequence->end());
}

#ifdef DEBUG
void test_solution() {
    auto timer = Timer();
    std::vector<unsigned> sequence;

    solution(1, &sequence);
    EXPECT_LE(timer.elapsed(), 1000);
    ASSERT_EQ(sequence.size() - 1, 0);
    ASSERT_THAT(sequence, testing::ElementsAre(1));

    timer.restart();
    sequence.clear();

    solution(5, &sequence);
    EXPECT_LE(timer.elapsed(), 1000);
    ASSERT_EQ(sequence.size() - 1, 3);
    ASSERT_THAT(sequence, testing::ElementsAre(1, 2, 4, 5));

    timer.restart();
    sequence.clear();

    solution(96234, &sequence);
    EXPECT_LE(timer.elapsed(), 1000);
    ASSERT_EQ(sequence.size() - 1, 14);
    ASSERT_THAT(
        sequence,
        testing::ElementsAre(1, 3, 9, 10, 11, 22, 66, 198, 594, 1782, 5346, 16038, 16039, 32078, 96234));
}
#endif
} // namespace

int main(int argc, char* argv[]) {
    if (argc == 1) {
        size_t n;
        std::cin >> n;

        std::vector<unsigned> sequence;
        solution(n, &sequence);

        std::cout << sequence.size() - 1 << std::endl;
        for (size_t i = 0; i < sequence.size(); ++i)
        std::cout << sequence[i] << " ";

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
