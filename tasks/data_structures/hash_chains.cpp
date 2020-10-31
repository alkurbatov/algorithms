#include <algorithm>
#include <iostream>
#include <list>
#include <string>
#include <vector>

#ifdef DEBUG
#include <gmock/gmock.h>
#include <gtest/gtest.h>

#include "utils/timer.h"
#endif

namespace {
struct Dictionary {
    explicit Dictionary(size_t buckets): m_buckets(buckets), m_records(buckets) {
    }

    void add(const std::string& string) {
        auto& data = m_records[hash(string, m_buckets)];

        auto it = std::find(data.begin(), data.end(), string);
        if (it == data.end())
            data.push_front(string);
    }

    void del(const std::string& string) {
        auto& data = m_records[hash(string, m_buckets)];

        if (data.empty())
            return;

        data.remove(string);
    }

    const std::string find(const std::string& string) const {
        auto& data = m_records[hash(string, m_buckets)];

        auto it = std::find(data.begin(), data.end(), string);
        if (it == data.end())
            return "no";

        return "yes";
    }

    const std::list<std::string> check(size_t index) const {
        return m_records[index];
    }

    static size_t hash(const std::string& string, size_t buckets) {
        unsigned long long sum = 0;
        const unsigned long long p = 1000000007;

        for (int i = string.length() - 1; i >= 0; --i)
            sum = (sum * 263 + static_cast<unsigned>(string[i])) % p;

        return sum % buckets;
    }

 private:
    size_t m_buckets;
    std::vector<std::list<std::string>> m_records;
};

#ifdef DEBUG
void test_case_1() {
    ASSERT_EQ(Dictionary::hash("world", 5), 4);
    ASSERT_EQ(Dictionary::hash("HellO", 5), 4);
    ASSERT_EQ(Dictionary::hash("luck", 5), 2);
    ASSERT_EQ(Dictionary::hash("GooD", 5), 2);

    ASSERT_EQ(Dictionary::hash("UjNkKtHxBwRj", 43), 24);
}

void test_case_2() {
    Timer timer;
    Dictionary dict(5);

    dict.add("world");
    dict.add("HellO");

    ASSERT_THAT(dict.check(4), testing::ElementsAre("HellO", "world"));

    ASSERT_EQ(dict.find("World"), "no");
    ASSERT_EQ(dict.find("world"), "yes");

    dict.del("world");
    ASSERT_THAT(dict.check(4), testing::ElementsAre("HellO"));

    dict.del("HellO");
    dict.add("luck");
    dict.add("GooD");

    ASSERT_THAT(dict.check(2), testing::ElementsAre("GooD", "luck"));

    dict.del("good");

    EXPECT_LE(timer.elapsed(), 1000);
}

void test_case_3() {
    Timer timer;
    Dictionary dict(4);

    dict.add("test");
    dict.add("test");

    ASSERT_EQ(dict.find("test"), "yes");

    dict.del("test");

    ASSERT_EQ(dict.find("test"), "no");
    ASSERT_EQ(dict.find("Test"), "no");

    dict.add("Test");
    ASSERT_EQ(dict.find("Test"), "yes");

    EXPECT_LE(timer.elapsed(), 1000);
}

void test_case_4() {
    Timer timer;
    Dictionary dict(3);

    ASSERT_THAT(dict.check(0), testing::ElementsAre());
    ASSERT_EQ(dict.find("help"), "no");

    dict.add("help");
    dict.add("del");
    dict.add("add");

    ASSERT_EQ(dict.find("add"), "yes");
    ASSERT_EQ(dict.find("del"), "yes");

    dict.del("del");

    ASSERT_EQ(dict.find("del"), "no");
    ASSERT_TRUE(dict.check(0).empty());
    ASSERT_THAT(dict.check(1), testing::ElementsAre("add", "help"));
    ASSERT_TRUE(dict.check(2).empty());

    EXPECT_LE(timer.elapsed(), 1000);
}

void test_case_5() {
    Timer timer;
    Dictionary dict(43);

    ASSERT_TRUE(dict.check(11).empty());

    dict.del("cwNqazSgq");

    ASSERT_EQ(dict.find("nvURhSyKS"), "no");
    ASSERT_EQ(dict.find("wAG"), "no");

    dict.add("CioXHYV");

    ASSERT_EQ(dict.find("eBxHRU"), "no");
    ASSERT_TRUE(dict.check(35).empty());
    ASSERT_TRUE(dict.check(31).empty());

    dict.add("t");

    ASSERT_EQ(dict.find("MZm"), "no");
    ASSERT_EQ(dict.find("s"), "no");
    ASSERT_EQ(dict.find("t"), "yes");
    ASSERT_EQ(dict.find("fIeyns"), "no");

    dict.add("laJZNL");
    dict.del("arZZXPp");
    dict.del("cHJjD");
    dict.add("vMWlPvkPvuf");
    dict.add("O");

    ASSERT_TRUE(dict.check(29).empty());
    ASSERT_EQ(dict.find(" ZuzOjbCxhYKl"), "no");

    dict.add("CioXHYV");
    dict.add("CdpInczxYRyfBj");

    ASSERT_TRUE(dict.check(4).empty());

    dict.add("gHUR");

    ASSERT_TRUE(dict.check(17).empty());
    ASSERT_EQ(dict.find("tUvsiIUxzUbdb"), "no");
    ASSERT_TRUE(dict.check(11).empty());
    ASSERT_EQ(dict.find("lKikJgNGhnPMgSE"), "no");
    ASSERT_EQ(dict.find("fKl"), "no");
    ASSERT_THAT(dict.check(19), testing::ElementsAre("gHUR"));
    ASSERT_EQ(dict.find("BqHlql"), "no");

    dict.del("SNK");
    dict.del("moedzmytBtth");
    dict.add("O");

    ASSERT_TRUE(dict.check(37).empty());
    ASSERT_TRUE(dict.check(24).empty());

    dict.del("CRvmMOn");
    dict.add("sZrzjJIf");

    ASSERT_TRUE(dict.check(6).empty());
    ASSERT_EQ(dict.find("snYyWMhYrKKtK"), "no");

    dict.del("F");
    dict.add("m");
    dict.del("nupqimflfTe");

    ASSERT_EQ(dict.find("FnIwVveUbm"), "no");

    dict.del("nISZ");
    dict.add("UjNkKtHxBwRj");
    dict.del("ydr");

    ASSERT_EQ(dict.find("fksIHIZtgwHQAJl"), "no");

    dict.add("fhzLy");

    ASSERT_TRUE(dict.check(42).empty());

    dict.add("pUvhkEQzm");
    dict.del("i");

    ASSERT_TRUE(dict.check(8).empty());

    dict.add("tWLfcAO");
    dict.del("t");

    ASSERT_TRUE(dict.check(14).empty());
    ASSERT_TRUE(dict.check(15).empty());
    ASSERT_EQ(dict.find("pFKwzJoYPRib"), "no");
    ASSERT_EQ(dict.find("JcKlh"), "no");

    dict.del("IjrYsmaQIECB");

    ASSERT_THAT(dict.check(36), testing::ElementsAre("O"));
    ASSERT_THAT(dict.check(7), testing::ElementsAre("laJZNL"));
    ASSERT_EQ(dict.find("K"), "no");
    ASSERT_EQ(dict.find("etIlCjME"), "no");
    ASSERT_TRUE(dict.check(18).empty());
    ASSERT_TRUE(dict.check(38).empty());

    dict.add("qvxNdIxpWrbbCS");
    dict.add("MSNFc");
    dict.add("Wrula");

    ASSERT_TRUE(dict.check(35).empty());

    dict.add("TN");
    dict.add("UVgxfLpJYCM");
    dict.add("pNYThzpnzX");

    ASSERT_EQ(dict.find("xffmYLB"), "no");
    ASSERT_EQ(dict.find("ICSGW"), "no");
    ASSERT_EQ(dict.find("L"), "no");

    dict.del("m");

    ASSERT_THAT(dict.check(24), testing::ElementsAre("UjNkKtHxBwRj"));

    dict.del("O");

    ASSERT_TRUE(dict.check(18).empty());
    ASSERT_EQ(dict.find("LfUWtcVaebHab"), "no");

    dict.add("Vzep");
    dict.add("MSNFc");
    dict.del("UeqCvdjfCzousF");
    dict.del("OsMWahyK");

    ASSERT_THAT(dict.check(5), testing::ElementsAre("MSNFc"));
    ASSERT_EQ(dict.find("kxeahgVrGVQR"), "no");
    ASSERT_THAT(dict.check(26), testing::ElementsAre("fhzLy"));

    dict.add("TN");

    ASSERT_THAT(dict.check(11), testing::ElementsAre("Vzep"));
    ASSERT_EQ(dict.find("QlEyEjLRWdUQTcO"), "no");
    ASSERT_EQ(dict.find("YQz"), "no");
    ASSERT_TRUE(dict.check(9).empty());

    dict.add("MzJyihsDPoLNGi");
    dict.del("RPpY");

    ASSERT_EQ(dict.find("NcYerUntZzUX"), "no");

    EXPECT_LE(timer.elapsed(), 1000);
}

void test_solution() {
    test_case_1();
    test_case_2();
    test_case_3();
    test_case_4();
    test_case_5();
}
#endif
}  // namespace

int main(int argc, char** argv) {
    if (argc == 1) {
        size_t num_buckets;
        std::cin >> num_buckets;

        size_t num_queries;
        std::cin >> num_queries;

        Dictionary dict(num_buckets);
        while(num_queries--) {
            std::string query;
            std::cin >> query;

            if (query == "add") {
                std::string string;
                std::cin >> string;

                dict.add(string);
                continue;
            }

            if (query == "del") {
                std::string string;
                std::cin >> string;

                dict.del(string);
                continue;
            }

            if (query == "find") {
                std::string string;
                std::cin >> string;

                std::cout << dict.find(string) << std::endl;
                continue;
            }

            if (query == "check") {
                size_t index;
                std::cin >> index;

                auto data = dict.check(index);
                if (!data.empty()) {
                    for(auto i : dict.check(index))
                        std::cout << i << " ";
                }

                std::cout << std::endl;
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
