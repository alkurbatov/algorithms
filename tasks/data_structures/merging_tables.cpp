#include <algorithm>
#include <iostream>
#include <vector>

#ifdef DEBUG
#include <string>
#include <gtest/gtest.h>

#include "utils/timer.h"
#endif

namespace {
const int ROOT = -1;

struct DisjointSet {
    size_t size = 0;
    int parent = ROOT;
    size_t rank = 0;
};

struct TablesList {
    explicit TablesList(const std::vector<size_t>& sizes):
        m_max_table_size(0), m_tables(sizes.size()) {
        for (size_t i = 0; i < sizes.size(); ++i) {
            m_tables[i].size = sizes[i];
            m_max_table_size = std::max(m_max_table_size, sizes[i]);
        }
    }

    unsigned getParent(unsigned table) {
        if (m_tables[table].parent == ROOT)
            return table;

        m_tables[table].parent = getParent(m_tables[table].parent);
        return m_tables[table].parent;
    }

    void merge(unsigned destination, unsigned source) {
        unsigned realDestination = getParent(--destination);
        unsigned realSource = getParent(--source);

        if (realDestination == realSource)
            return;

        if (m_tables[realDestination].rank > m_tables[realSource].rank)
            link(realSource, realDestination);
        else {
            if (m_tables[realDestination].rank == m_tables[realSource].rank)
                m_tables[realSource].rank += 1;

            link(realDestination, realSource);
        }

        m_max_table_size = std::max(m_max_table_size, m_tables[realDestination].size);
    }

    size_t maxTableSize() const {
        return m_max_table_size;
    }

    void print() const {
        for (auto table : m_tables) {
            std::cout <<
                "size: " << table.size <<
                " parent: " << table.parent <<
                " rank: " << table.rank <<
                std::endl;
        }

        std::cout << "-----" << std::endl;
    }

 private:
    void link(unsigned destination, unsigned source) {
        m_tables[destination].size += m_tables[source].size;
        m_tables[source].size = 0;
        m_tables[source].parent = destination;
    }

    size_t m_max_table_size;
    std::vector <DisjointSet> m_tables;
};

#ifdef DEBUG
void test_case_1() {
    Timer timer;
    TablesList tables({ 1, 1, 1, 1, 1 });
    tables.print();

    tables.merge(3, 5);
    tables.print();
    ASSERT_EQ(tables.maxTableSize(), 2);

    tables.merge(2, 4);
    tables.print();
    ASSERT_EQ(tables.maxTableSize(), 2);

    tables.merge(1, 4);
    tables.print();
    ASSERT_EQ(tables.maxTableSize(), 3);

    tables.merge(5, 4);
    tables.print();
    ASSERT_EQ(tables.maxTableSize(), 5);

    tables.merge(5, 3);
    tables.print();
    ASSERT_EQ(tables.maxTableSize(), 5);

    EXPECT_LE(timer.elapsed(), 2000);
}

void test_case_2() {
    Timer timer;
    TablesList tables({ 10, 0, 5, 0, 3, 3 });
    tables.print();

    tables.merge(6, 6);
    tables.print();
    ASSERT_EQ(tables.maxTableSize(), 10);

    tables.merge(6, 5);
    tables.print();
    ASSERT_EQ(tables.maxTableSize(), 10);

    tables.merge(5, 4);
    tables.print();
    ASSERT_EQ(tables.maxTableSize(), 10);

    tables.merge(4, 3);
    tables.print();
    ASSERT_EQ(tables.maxTableSize(), 11);

    EXPECT_LE(timer.elapsed(), 2000);
}

void test_solution() {
    test_case_1();
    test_case_2();
}
#endif
}  // namespace

int main(int argc, char** argv) {
    if (argc == 1) {
        size_t n, m;
        std::cin >> n >> m;

        std::vector<size_t> table_sizes;
        for (size_t i = 0; i < n; ++i) {
            unsigned size;
            std::cin >> size;
            table_sizes.push_back(size);
        }

        TablesList tables(table_sizes);
        for (size_t i = 0; i < m; ++i) {
            unsigned destination, source;
            std::cin >> destination >> source;

            tables.merge(destination, source);
            std::cout << tables.maxTableSize() << std::endl;
        }

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
