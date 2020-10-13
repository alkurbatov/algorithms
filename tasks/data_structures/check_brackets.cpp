#include <iostream>
#include <stack>
#include <string>

#ifdef DEBUG
#include <gtest/gtest.h>

#include "utils/timer.h"
#endif

struct Bracket {
    Bracket(char type, int position):
        type(type), position(position) {
    }

    bool match(char c) const {
        return (type == '[' && c == ']')
            || (type == '{' && c == '}')
            || (type == '(' && c == ')');
    }

    char type;
    int position;
};

int solution(const std::string& text) {
    std::stack<Bracket> stack;

    for (int position = 0; position < text.length(); ++position) {
        char c = text[position];

        if (c == '(' || c == '[' || c == '{') {
            stack.emplace(c, position);
            continue;
        }

        if (c == ')' || c == ']' || c == '}') {
            if (stack.empty() || !stack.top().match(c))
                return position + 1;

            stack.pop();
            continue;
        }
    }

    return stack.empty() ? -1 : stack.top().position + 1;
}

#ifdef DEBUG
void test_solution() {
    auto timer = Timer();
    ASSERT_EQ(solution("[]"), -1);
    EXPECT_LE(timer.elapsed(), 1000);

    timer.restart();
    ASSERT_EQ(solution("{}[]"), -1);
    EXPECT_LE(timer.elapsed(), 1000);

    timer.restart();
    ASSERT_EQ(solution("[()]"), -1);
    EXPECT_LE(timer.elapsed(), 1000);

    timer.restart();
    ASSERT_EQ(solution("(())"), -1);
    EXPECT_LE(timer.elapsed(), 1000);

    timer.restart();
    ASSERT_EQ(solution("{[]}()"), -1);
    EXPECT_LE(timer.elapsed(), 1000);

    timer.restart();
    ASSERT_EQ(solution("{"), 1);
    EXPECT_LE(timer.elapsed(), 1000);

    timer.restart();
    ASSERT_EQ(solution("}"), 1);
    EXPECT_LE(timer.elapsed(), 1000);

    timer.restart();
    ASSERT_EQ(solution("{[}"), 3);
    EXPECT_LE(timer.elapsed(), 1000);

    timer.restart();
    ASSERT_EQ(solution("foo(bar);"), -1);
    EXPECT_LE(timer.elapsed(), 1000);

    timer.restart();
    ASSERT_EQ(solution("foo(bar[i);"), 10);
    EXPECT_LE(timer.elapsed(), 1000);
}
#endif

int main(int argc, char* argv[]) {
    if (argc == 1) {
        std::string text;
        getline(std::cin, text);

        int position = solution(text);
        if (position == -1) {
            std::cout << "Success" << std::endl;
            return 0;
        }

        std::cout << position << std::endl;
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
