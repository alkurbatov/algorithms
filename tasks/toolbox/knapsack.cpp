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


unsigned solution(size_t capacity, const std::vector<unsigned>& items) {
    Matrix path_matrix(items.size() + 1, capacity + 1);

    for (size_t i = 1; i <= items.size(); ++i) {
        for (size_t w = 1; w <= capacity; ++w) {
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

    return path_matrix.get(items.size(), capacity);
}

#ifdef DEBUG
void test_solution() {
    auto timer = Timer();
    ASSERT_EQ(solution(10, { 1, 4, 8 }), 9);
    EXPECT_LE(timer.elapsed(), 1000);
}
#endif
} // namespace

int main(int argc, char* argv[]) {
    if (argc == 1) {
        size_t n, W;
        std::cin >> W >> n;

        std::vector<unsigned> w(n);
        for (size_t i = 0; i < n; ++i)
            std::cin >> w[i];

        std::cout << solution(W, w) << std::endl;
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
