#include <iostream>
#include <numeric>
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
        for(size_t i = 0; i < m_matrix.size(); ++i) {
            std::cout << m_matrix[i] << " ";

            if ((i + 1) % m_columns == 0)
                std::cout << std::endl;
        }
    }

 private:
    size_t m_columns;
    std::vector<unsigned> m_matrix;
};


bool solution(const std::vector<unsigned>& items) {
    unsigned full_capacity = std::accumulate(items.begin(), items.end(), 0);
    if (full_capacity % 3)
        return false;

    unsigned partition = full_capacity / 3;

    Matrix path_matrix(items.size() + 1, partition + 1);

    for (unsigned i = 1; i <= items.size(); ++i) {
        for (unsigned w = 1; w <= partition; ++w) {
            path_matrix.set(i, w, path_matrix.get(i - 1, w));

            if (items[i - 1] > w)
                continue;

            unsigned val =  path_matrix.get(i - 1, w - items[i - 1]) + items[i - 1];
            if (path_matrix.get(i, w) < val)
                path_matrix.set(i, w, val);
        }
    }

#ifdef DEBUG
    path_matrix.print();
#endif

    unsigned counter = 0;
    for (unsigned i = 1; i <= items.size(); ++i)
        counter += static_cast<unsigned>(path_matrix.get(i, partition) == partition);

    return counter >= 3;
}

#ifdef DEBUG
void test_solution() {
    auto timer = Timer();
    ASSERT_EQ(solution({ 3, 3, 3, 3 }), 0);
    EXPECT_LE(timer.elapsed(), 1000);

    timer.restart();
    ASSERT_EQ(solution({ 40 }), 0);
    EXPECT_LE(timer.elapsed(), 1000);

    timer.restart();
    ASSERT_EQ(solution({ 2, 3, 4, 5, 7 }), 1);
    EXPECT_LE(timer.elapsed(), 1000);

    timer.restart();
    ASSERT_EQ(solution({ 17, 59, 34, 57, 17, 23, 67, 1, 18, 2, 59 }), 1);
    EXPECT_LE(timer.elapsed(), 1000);

    timer.restart();
    ASSERT_EQ(solution({ 1, 2, 3, 4, 5, 5, 7, 7, 8, 10, 12, 19, 25 }), 1);
    EXPECT_LE(timer.elapsed(), 1000);
}
#endif
} // namespace

int main(int argc, char* argv[]) {
    if (argc == 1) {
        unsigned n;
        std::cin >> n;

        std::vector<unsigned> items(n);
        for (unsigned i = 0; i < n; ++i)
            std::cin >> items[i];

        std::cout << solution(items) << std::endl;
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
