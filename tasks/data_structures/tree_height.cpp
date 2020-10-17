#include <iostream>
#include <vector>

#ifdef DEBUG
#include <gtest/gtest.h>

#include "utils/timer.h"
#endif

namespace {
const int ROOT = -1;

struct Node {
    Node(): key(0), parent(nullptr) {
    }

    void setParent(Node* theParent) {
      parent = theParent;
      parent->children.push_back(this);
    }

    int key;
    Node *parent;
    std::vector<Node*> children;
};

unsigned solution(const std::vector<int>& src) {
    std::vector<Node> nodes(src.size());

    unsigned root_index = 0;
    for (unsigned i = 0; i < src.size(); ++i) {
      int parent_index = src[i];

      if (parent_index >= 0)
        nodes[i].setParent(&nodes[parent_index]);
      else
        root_index = i;

      nodes[i].key = i;
    }

    if (nodes.empty())
        return 0;

    unsigned height = 0;
    std::vector<Node*> current_level;
    std::vector<Node*> next_level;
    current_level.push_back(&nodes[root_index]);

    while(!current_level.empty()) {
        for (auto i : current_level) {
            if (i->children.empty())
                continue;

            next_level.insert(next_level.end(), i->children.begin(), i->children.end());
        }

        ++height;
        current_level = next_level;
        next_level.clear();
    }

    return height;
}

#ifdef DEBUG
void test_solution() {
    auto timer = Timer();

    ASSERT_EQ(solution({ 4, ROOT, 4, 1, 1 }), 3);
    EXPECT_LE(timer.elapsed(), 1000);

    timer.restart();

    ASSERT_EQ(solution({ ROOT, 0, 4, 0, 3 }), 4);
    EXPECT_LE(timer.elapsed(), 1000);

    timer.restart();

    ASSERT_EQ(solution({}), 0);
    EXPECT_LE(timer.elapsed(), 1000);
}
#endif
}  // namespace

int main (int argc, char** argv) {
    if (argc == 1) {
        unsigned n;
        std::cin >> n;

        int key;
        std::vector<int> input;
        while(std::cin >> key)
            input.push_back(key);

        std::cout << solution(input) << std::endl;

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
