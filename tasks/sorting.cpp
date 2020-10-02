#include <iostream>
#include <vector>
#include <utility>

#ifdef DEBUG
#include <gtest/gtest.h>

#include "utils/timer.h"
#endif

namespace {
std::pair<unsigned, unsigned> partition3(std::vector<long long>& a, unsigned l, unsigned r) {
    long long x = a[l];
    unsigned begin = l;
    unsigned end = l;

    for (int i = l + 1; i <= r; ++i) {
        if (a[i] > x)
            continue;

        if (a[i] < x) {
            ++end;
            std::swap(a[i], a[end]);
            std::swap(a[begin], a[end]);
            ++begin;
            continue;
        }

        if (a[i] == x) {
            ++end;
            std::swap(a[i], a[end]);
            continue;
        }
    }

    return std::make_pair(begin, end);
}

void randomized_quick_sort(std::vector<long long>& a, int l, int r) {
    if (l >= r)
        return;

    unsigned k = l + rand() % (r - l + 1);
    std::swap(a[l], a[k]);
    std::pair<unsigned, unsigned> m = partition3(a, l, r);

    randomized_quick_sort(a, l, m.first - 1);
    randomized_quick_sort(a, m.second + 1, r);
}

#ifdef DEBUG
void test_solution() {
    std::vector<long long> data{ 2, 3, 9, 2, 2 };
    std::vector<long long> expected{ 2, 2, 2, 3, 9 };

    auto timer = Timer();
    randomized_quick_sort(data, 0, data.size() - 1);

    ASSERT_LE(timer.elapsed(), 1000);
    for (size_t i = 0; i < data.size(); ++i)
        ASSERT_EQ(data[i], expected[i]);

    data.assign({ 2, 3, 9, 2, 9 });
    expected.assign({ 2, 2, 3, 9, 9 });

    timer.restart();
    randomized_quick_sort(data, 0, data.size() - 1);

    ASSERT_LE(timer.elapsed(), 1000);
    for (size_t i = 0; i < data.size(); ++i)
        ASSERT_EQ(data[i], expected[i]);

    data.assign({ 2, 2, 9, 3, 1, 7, 1 });
    expected.assign({ 1, 1, 2, 2, 3, 7, 9 });

    timer.restart();
    randomized_quick_sort(data, 0, data.size() - 1);

    ASSERT_LE(timer.elapsed(), 1000);
    for (size_t i = 0; i < data.size(); ++i)
        ASSERT_EQ(data[i], expected[i]);
}
#endif
} // namespace

int main(int argc, char* argv[]) {
    if (argc == 1) {
        unsigned n;
        std::cin >> n;

        std::vector<long long> a(n);
        for (size_t i = 0; i < a.size(); ++i)
            std::cin >> a[i];

        randomized_quick_sort(a, 0, a.size() - 1);

        for (auto i : a)
            std::cout << i << ' ';

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
