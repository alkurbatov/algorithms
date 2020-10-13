#include <algorithm>
#include <iostream>
#include <vector>

#ifdef DEBUG
#include <gtest/gtest.h>

#include "utils/timer.h"
#endif

namespace {
bool has_majority_element(const std::vector<unsigned long>& data) {
    std::vector<unsigned long> sorted_data(data.size());
    std::partial_sort_copy(data.begin(), data.end(), sorted_data.begin(), sorted_data.end());

    unsigned majority = data.size() / 2 + 1;

    unsigned count = 1;
    unsigned long current = sorted_data[0];
    for (int i = 1; i < sorted_data.size(); ++i) {
        if (current != sorted_data[i]) {
            current = sorted_data[i];
            count = 1;
            continue;
        }

        if (++count == majority)
            return true;
    }

    return false;
}

#ifdef DEBUG
void test_solution() {
    std::vector<unsigned long> data{ 2, 3, 9, 2, 2 };
    auto timer = Timer();

    ASSERT_TRUE(has_majority_element(data));
    EXPECT_LE(timer.elapsed(), 1000);

    data.assign({ 1, 2, 3, 4 });
    timer.restart();

    ASSERT_FALSE(has_majority_element(data));
    EXPECT_LE(timer.elapsed(), 1000);

    data.assign({ 1, 2, 3, 1 });
    timer.restart();

    ASSERT_FALSE(has_majority_element(data));
    EXPECT_LE(timer.elapsed(), 1000);
}
#endif
} // namespace

int main(int argc, char* argv[]) {
    if (argc == 1) {
      size_t n;
      std::cin >> n;

      std::vector<unsigned long> a(n);
      for (size_t i = 0; i < a.size(); ++i)
        std::cin >> a[i];

        std::cout << has_majority_element(a) << std::endl;
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
