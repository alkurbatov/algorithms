#include <iostream>
#include <vector>

#ifdef DEBUG
#include <gtest/gtest.h>
#endif

namespace {
const int NOT_FOUND = -1;

int binary_search(const std::vector<unsigned long>& data, unsigned long key) {
    int left = 0;
    int right = data.size() - 1;

    while (right >= left) {
        size_t med = left + (right - left) / 2;

        if (data[med] == key)
            return med;

        if (data[med] > key) {
            right = med - 1;
            continue;
        }

        if (data[med] < key) {
            left = med + 1;
            continue;
        }
    }

    return NOT_FOUND;
}

#ifdef DEBUG
void test_solution() {
    std::vector<unsigned long> a{1, 5, 8, 12, 13};

    EXPECT_EQ(binary_search(a, 8), 2);
    EXPECT_EQ(binary_search(a, 1), 0);
    EXPECT_EQ(binary_search(a, 23), NOT_FOUND);
    EXPECT_EQ(binary_search(a, 1), 0);
    EXPECT_EQ(binary_search(a, 11), NOT_FOUND);

    a.assign({1, 2, 3, 4, 5});

    EXPECT_EQ(binary_search(a, 1), 0);
    EXPECT_EQ(binary_search(a, 2), 1);
    EXPECT_EQ(binary_search(a, 3), 2);
    EXPECT_EQ(binary_search(a, 4), 3);
    EXPECT_EQ(binary_search(a, 5), 4);
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

        size_t m;
        std::cin >> m;
        std::vector<unsigned long> b(m);
        for (size_t i = 0; i < m; ++i)
            std::cin >> b[i];

        for (size_t i = 0; i < m; ++i)
            std::cout << binary_search(a, b[i]) << ' ';

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
