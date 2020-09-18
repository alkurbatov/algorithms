#include <algorithm>
#include <iostream>
#include <vector>

#ifdef DEBUG
#include <gtest/gtest.h>

#include "utils/timer.h"
#endif

namespace {
long int solution(const std::vector<long int>& values, const std::vector<long int>& clicks) {
    std::vector<long int> sorted_values(values.size());
    std::partial_sort_copy(values.begin(), values.end(), sorted_values.begin(), sorted_values.end());

    std::vector<long int> sorted_clicks(clicks.size());
    std::partial_sort_copy(clicks.begin(), clicks.end(), sorted_clicks.begin(), sorted_clicks.end());

    long int n = 0;
    for (int i = 0; i < sorted_values.size(); ++i)
        n += sorted_values[i] * sorted_clicks[i];

    return n;
}

#ifdef DEBUG
void test_solution() {
    std::vector<long int> values{23};
    std::vector<long int> clicks{39};

    auto timer = Timer();
    EXPECT_EQ(solution(values, clicks), 897);
    ASSERT_LE(timer.elapsed(), 1000);

    values.assign({1, 3, -5});
    clicks.assign({-2, 4, 1});

    timer.restart();
    EXPECT_EQ(solution(values, clicks), 23);
    ASSERT_LE(timer.elapsed(), 1000);
}
#endif
} // namespace

int main(int argc, char* argv[]) {
    if (argc == 1) {
        size_t n;
        std::cin >> n;

        std::vector<long int> values(n), clicks(n);
        for (size_t i = 0; i < n; ++i)
            std::cin >> values[i];
        for (size_t i = 0; i < n; ++i)
            std::cin >> clicks[i];

        std::cout << solution(values, clicks) << std::endl;
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
