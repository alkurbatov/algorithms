#include <iostream>
#include <string>
#include <vector>

#ifdef DEBUG
#include <gtest/gtest.h>

#include "utils/timer.h"
#endif

namespace {
unsigned min(unsigned a, unsigned b, unsigned c) {
    return std::min(a, std::min(b, c));
}

struct Matrix {
    Matrix(unsigned rows, unsigned columns):
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
    unsigned m_columns;
    std::vector<unsigned> m_matrix;
};

unsigned solution(const std::string& str1, const std::string& str2) {
    Matrix path_matrix(str1.length() + 1, str2.length() + 1);

    for (size_t i = 0; i <= str1.length(); ++i)
        path_matrix.set(i, 0, i);

    for (size_t j = 0; j <= str2.length(); ++j)
        path_matrix.set(0, j, j);

    for (size_t j = 1; j <= str2.length(); ++j) {
        for (size_t i = 1; i <= str1.length(); ++i) {
            unsigned insertion = path_matrix.get(i, j - 1) + 1;
            unsigned deletion = path_matrix.get(i - 1, j) + 1;
            unsigned match = path_matrix.get(i - 1, j - 1);
            unsigned mismatch = path_matrix.get(i - 1, j - 1) + 1;

            if (str1[i - 1] == str2[j - 1]) {
                path_matrix.set(i, j, min(insertion, deletion, match));
                continue;
            }

            path_matrix.set(i, j, min(insertion, deletion, mismatch));
        }
    }

#ifdef DEBUG
    path_matrix.print();
#endif

    return path_matrix.get(str1.length(), str2.length());
}

#ifdef DEBUG
void test_solution() {
    Timer timer;
    ASSERT_EQ(solution("ab", "ab"), 0);
    EXPECT_LE(timer.elapsed(), 1000);

    timer.restart();
    ASSERT_EQ(solution("short", "ports"), 3);
    EXPECT_LE(timer.elapsed(), 1000);

    timer.restart();
    ASSERT_EQ(solution("editing", "distance"), 5);
    EXPECT_LE(timer.elapsed(), 1000);
}
#endif
} // namespace

int main(int argc, char* argv[]) {
    if (argc == 1) {
        std::string str1;
        std::string str2;
        std::cin >> str1 >> str2;

        std::cout << solution(str1, str2) << std::endl;
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
