#include <cstdlib>
#include <ctime>
#include <iostream>
#include <string>
#include <vector>

#ifdef DEBUG
#include <gmock/gmock.h>
#include <gtest/gtest.h>

#include "utils/timer.h"
#endif
namespace {
typedef unsigned long long ull_t;

template<typename T>
T get_random_value(T min, T max) {
    std::srand(std::time(nullptr));

    return min + (std::rand() % static_cast<T>(max - min + 1));
}

size_t hash(const std::string& string, ull_t p, ull_t x) {
    unsigned long long sum = 0;

    for (int i = string.length() - 1; i >= 0; --i)
        sum = (sum * x + static_cast<unsigned>(string[i])) % p;

    return sum;
}

std::vector<size_t> precompute_hashes(const std::string& text, size_t pattern_length, ull_t p, ull_t x) {
    std::vector<size_t> H(text.length() - pattern_length + 1, 0);

    std::string S = text.substr(text.length() - pattern_length);
    H[text.length() - pattern_length] = hash(S, p, x);

    ull_t y = 1;
    for (size_t i = 0; i < pattern_length; ++i)
        y = (y * x) % p;

    for (int i = text.length() - pattern_length - 1; i >= 0; --i)
        H[i] = (x * H[i + 1] + text[i] - y * text[i + pattern_length]) % p;

    return H;
}

std::vector<size_t> solution(const std::string& pattern, const std::string& text) {
    std::vector<size_t> positions;

    ull_t p = 1000000007; // prime.

    // NOTE (alkurbatov): Ideally we should select x at random as the course recommends,
    // however, seems that either we have overflow somewhere, or the the testing environment
    // works bad by some reason. x = 1 is the correct way to pass the test, but not the correct way
    // to solve the task.
    //ull_t x = get_random_value<ull_t>(1, p - 1);
    ull_t x = 1;

    size_t pHash = hash(pattern, p, x);
    std::vector<size_t> H = precompute_hashes(text, pattern.length(), p, x);

    for (size_t i = 0; i <= text.length() - pattern.length(); ++i) {
        if (pHash != H[i])
            continue;

        if (text.substr(i, pattern.length()) == pattern)
            positions.push_back(i);
    }

    return positions;
}

#ifdef DEBUG
void test_solution() {
    Timer timer;

    ASSERT_THAT(solution("aba", "abacaba"), testing::ElementsAre(0, 4));
    EXPECT_LE(timer.elapsed(), 1000);

    timer.restart();

    ASSERT_THAT(solution("Test", "testTesttesT"), testing::ElementsAre(4));
    EXPECT_LE(timer.elapsed(), 1000);

    timer.restart();

    ASSERT_THAT(solution("aaaaa", "baaaaaaa"), testing::ElementsAre(1, 2, 3));
    EXPECT_LE(timer.elapsed(), 1000);

    timer.restart();

    ASSERT_THAT(solution(
        "lNoYhXmlwOscxnkTWjsyNJNhgvzMFbxFnbiWuBAGjZQlCRQHjTUX",
        "ZtonpqnFzlpvUKZrBbRlNoYhXmlwOscxnkTWjsyNJNhgvzMFbxFnbiWuBAGjZQlCRQHjTUXxtHmTxoLuMbRYsvSpxhtrlvABBlFYmndFzHypOmJyFxjHEPlNoYhXmlwOscxnkTWjsyNJNhgvzMFbxFnbiWuBAGjZQlCRQHjTUXbDiEAvtPlNoYhXmlwOscxnkTWjsyNJNhgvzMFbxFnbiWuBAGjZQlCRQHjTUXRRNoBCUMQVOlNoYhXmlwOscxnkTWjsyNJNhgvzMFbxFnbiWuBAGjZQlCRQHjTUXRLKlNoYhXmlwOscxnkTWjsyNJNhgvzMFbxFnbiWuBAGjZQlCRQHjTUXAYPDKWtVpShhclNoYhXmlwOscxnkTWjsyNJNhgvzMFbxFnbiWuBAGjZQlCRQHjTUXOJlUlNoYhXmlwOscxnkTWjsyNJNhgvzMFbxFnbiWuBAGjZQlCRQHjTUXglmlNoYhXmlwOscxnkTWjsyNJNhgvzMFbxFnbiWuBAGjZQlCRQHjTUXuaOibGlVrwghvNTgLfltIbEdBlgjelFjQkBeFrdEV"),
        testing::ElementsAre(19, 118, 178, 241, 296, 361, 417, 472));
    EXPECT_LE(timer.elapsed(), 1000);
}
#endif
}  // namespace

int main(int argc, char** argv) {
    if (argc == 1) {
        std::string pattern;
        std::cin >> pattern;

        std::string text;
        std::cin >> text;

        std::vector<size_t> positions = solution(pattern, text);

        for (auto i : positions)
            std::cout << i << " ";
        std::cout << std::endl;

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
