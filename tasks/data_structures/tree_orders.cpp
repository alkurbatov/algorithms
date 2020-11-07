#include <algorithm>
#include <iostream>
#include <stack>
#include <vector>

#ifdef DEBUG
#include <gmock/gmock.h>
#include <gtest/gtest.h>

#include "utils/timer.h"
#endif

namespace {
struct Node {
    unsigned key = 0;
    int left = -1;
    int right = -1;
};

struct BinaryTree {
    void addNode(const Node& node) {
        m_nodes.push_back(node);
    }

    std::vector<unsigned> inOrderTraversal() const {
        std::vector<unsigned> result;

        std::stack<Node> children;
        children.push(m_nodes[0]);

        while(!children.empty()) {
            if (children.top().left > -1) {
                Node& n = children.top();
                children.push(m_nodes[n.left]);
                n.left = -1;
                continue;
            }

            Node n = children.top();
            children.pop();
            result.push_back(n.key);

            if (n.right > -1)
                children.push(m_nodes[n.right]);
        }

        return result;
    }

    std::vector<unsigned> preOrderTraversal() const {
        std::vector<unsigned> result;

        std::stack<Node> children;
        children.push(m_nodes[0]);

        while(!children.empty()) {
            Node n = children.top();
            children.pop();

            result.push_back(n.key);

            if (n.right > -1)
                children.push(m_nodes[n.right]);

            if (n.left > -1)
                children.push(m_nodes[n.left]);
        }

        return result;
    }

    std::vector<unsigned> postOrderTraversal() const {
        std::vector<unsigned> result;

        std::stack<Node> children;
        children.push(m_nodes[0]);

        while(!children.empty()) {
            Node n = children.top();
            children.pop();

            if (n.left > -1)
                children.push(m_nodes[n.left]);

            if (n.right > -1)
                children.push(m_nodes[n.right]);

            result.push_back(n.key);
        }

        std::reverse(result.begin(), result.end());
        return result;
    }

    void clear() {
        m_nodes.clear();
    }

 private:
    std::vector<Node> m_nodes;
};

void print_vector(const std::vector<unsigned>& data) {
    for (auto i : data)
        std::cout << i << " ";
    std::cout << std::endl;
}

#ifdef DEBUG
void test_solution() {
    Timer timer;

    BinaryTree tree;
    tree.addNode({4, 1, 2});
    tree.addNode({2, 3, 4});
    tree.addNode({5, -1, -1});
    tree.addNode({1, -1, -1});
    tree.addNode({3, -1, -1});

    ASSERT_THAT(tree.inOrderTraversal(), testing::ElementsAre(1, 2, 3, 4, 5));
    ASSERT_THAT(tree.preOrderTraversal(), testing::ElementsAre(4, 2, 1, 3, 5));
    ASSERT_THAT(tree.postOrderTraversal(), testing::ElementsAre(1, 3, 2, 5, 4));
    EXPECT_LE(timer.elapsed(), 1000);

    timer.restart();

    tree.clear();
    tree.addNode({0, 7, 2});
    tree.addNode({10, -1, -1});
    tree.addNode({20, -1, 6});
    tree.addNode({30, 8, 9});
    tree.addNode({40, 3, -1});
    tree.addNode({50, -1, -1});
    tree.addNode({60, 1, -1});
    tree.addNode({70, 5, 4});
    tree.addNode({80, -1, -1});
    tree.addNode({90, -1, -1});

    ASSERT_THAT(tree.inOrderTraversal(), testing::ElementsAre(50, 70, 80, 30, 90, 40, 0, 20, 10, 60));
    ASSERT_THAT(tree.preOrderTraversal(), testing::ElementsAre(0, 70, 50, 40, 30, 80, 90, 20, 60, 10));
    ASSERT_THAT(tree.postOrderTraversal(), testing::ElementsAre(50, 80, 90, 30, 40, 70, 10, 60, 20, 0));
    EXPECT_LE(timer.elapsed(), 1000);
}
#endif
}  // namespace

int main(int argc, char** argv) {
    if (argc == 1) {
        size_t vertices;
        std::cin >> vertices;

        BinaryTree tree;
        for (size_t i = 0; i < vertices; ++i) {
            Node n;
            std::cin >> n.key >> n.left >> n.right;
            tree.addNode(n);
        }

        print_vector(tree.inOrderTraversal());
        print_vector(tree.preOrderTraversal());
        print_vector(tree.postOrderTraversal());

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
