#include <iostream>
#include <string>
#include <vector>

#ifdef DEBUG
#include <gtest/gtest.h>

#include "utils/timer.h"
#endif

namespace {
const char* NOT_FOUND = "not found";

struct PhoneBook {
    PhoneBook():  m_records(10000000) {
    }

    void add(unsigned number, const std::string& name) {
        m_records[number] = name;
    }

    void del(unsigned number) {
        m_records[number] = "";
    }

    const std::string find(unsigned number) const {
        if (m_records[number].empty())
            return NOT_FOUND;

        return m_records[number];
    }

 private:
    std::vector<std::string> m_records;
};

#ifdef DEBUG
void test_case_1() {
    Timer timer;
    PhoneBook book;

    book.add(911, "police");
    book.add(76213, "Mom");
    book.add(17239, "Bob");

    ASSERT_EQ(book.find(76213), "Mom");
    ASSERT_EQ(book.find(910), NOT_FOUND);
    ASSERT_EQ(book.find(911), "police");

    book.del(910);
    book.del(911);

    ASSERT_EQ(book.find(911), NOT_FOUND);
    ASSERT_EQ(book.find(76213), "Mom");

    book.add(76213, "daddy");

    ASSERT_EQ(book.find(76213), "daddy");

    EXPECT_LE(timer.elapsed(), 3000);
}

void test_case_2() {
    Timer timer;
    PhoneBook book;

    ASSERT_EQ(book.find(3839442), NOT_FOUND);

    book.add(123456, "me");
    book.add(0, "granny");

    ASSERT_EQ(book.find(0), "granny");
    ASSERT_EQ(book.find(123456), "me");

    book.del(0);
    book.del(0);

    ASSERT_EQ(book.find(0), NOT_FOUND);
}

void test_solution() {
    test_case_1();
    test_case_2();
}
#endif
}  // namespace

int main(int argc, char** argv) {
    if (argc == 1) {
        size_t num_queries;
        std::cin >> num_queries;

        PhoneBook book;
        while(num_queries--) {
            std::string query;
            std::cin >> query;

            unsigned number;
            std::cin >> number;

            if (query == "add") {
                std::string name;
                std::cin >> name;

                book.add(number, name);
                continue;
            }

            if (query == "del") {
                book.del(number);
                continue;
            }

            if (query == "find") {
                std::cout << book.find(number) << std::endl;
                continue;
            }
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
