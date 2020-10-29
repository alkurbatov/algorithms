#include <iostream>
#include <vector>

#ifdef DEBUG
#include <gtest/gtest.h>

#include "utils/timer.h"
#endif

namespace {
struct Matrix {
    Matrix(size_t rows, size_t columns):
        m_columns(columns), m_matrix(rows*columns, 0) {
    }

    void set(unsigned i, unsigned j, unsigned value) {
        m_matrix[i*m_columns + j] = value;
    }

    unsigned get(unsigned i, unsigned j) const {
        return m_matrix[i*m_columns + j];
    }

    void print() const {
        for (size_t i = 0; i < m_matrix.size(); ++i) {
            std::cout << m_matrix[i] << " ";

            if ((i + 1) % m_columns == 0)
                std::cout << std::endl;
        }
    }

 private:
    size_t m_columns;
    std::vector<unsigned> m_matrix;
};

unsigned solution(const std::vector<long int>& a, const std::vector<long int>& b) {
    Matrix path_matrix(a.size() + 1, b.size() + 1);

    for (size_t j = 1; j <= b.size(); ++j) {
        for (size_t i = 1; i <= a.size(); ++i) {
            if (a[i - 1] == b[j - 1]) {
                path_matrix.set(i, j, path_matrix.get(i - 1, j - 1) + 1);
                continue;
            }

            path_matrix.set(i, j, std::max(path_matrix.get(i - 1, j), path_matrix.get(i, j - 1)));
        }
    }

#ifdef DEBUG
    path_matrix.print();
#endif

    return path_matrix.get(a.size(), b.size());
}

#ifdef DEBUG
void test_solution() {
    auto timer = Timer();
    ASSERT_EQ(solution({ 2, 7, 5 }, { 2, 5 }), 2);
    EXPECT_LE(timer.elapsed(), 1000);

    timer.restart();
    ASSERT_EQ(solution({ -7 }, { -7 }), 1);
    EXPECT_LE(timer.elapsed(), 1000);

    timer.restart();
    ASSERT_EQ(solution({ -7 }, { 7 }), 0);
    EXPECT_LE(timer.elapsed(), 1000);

    timer.restart();
    ASSERT_EQ(solution({ 7 }, { 1, 2, 3, 4 }), 0);
    EXPECT_LE(timer.elapsed(), 1000);

    timer.restart();
    ASSERT_EQ(solution({ 2, 7, 8, 3 }, { 5, 2, 8, 7 }), 2);
    EXPECT_LE(timer.elapsed(), 1000);

    timer.restart();
    ASSERT_EQ(solution({ 1, 2, 3, 4, 5, 6, 7 }, { 1, 2, 3, 4, 5, 6, 7 }), 7);
    EXPECT_LE(timer.elapsed(), 1000);

    timer.restart();
    ASSERT_EQ(solution({ -1, -2, -3, -4, -5, -6, -7 }, { -1, -2, -3, -4, -5, -6, -7 }), 7);
    EXPECT_LE(timer.elapsed(), 1000);
}
#endif
} // namespace

int main(int argc, char* argv[]) {
    if (argc == 1) {
        size_t n;
        std::cin >> n;

        std::vector<long int> a(n);
        for (size_t i = 0; i < n; ++i)
            std::cin >> a[i];

        size_t m;
        std::cin >> m;

        std::vector<long int> b(m);
        for (size_t i = 0; i < m; ++i)
            std::cin >> b[i];

        std::cout << solution(a, b) << std::endl;
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
