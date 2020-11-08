#include <iostream>
#include <memory>
#include <queue>
#include <stack>
#include <vector>

#ifdef DEBUG
#include <gtest/gtest.h>

#include "utils/timer.h"
#endif

namespace {
struct Node {
    int index = -1;
    long int key = 0;
    int left = -1;
    int right = -1;
};

struct Tree {
    void addNode(long int key, int left, int right) {
        m_nodes.push_back({static_cast<int>(m_nodes.size()), key, left, right});
    }

    bool isBst() const {
        if (m_nodes.empty())
            return true;

        std::stack<Node> children;
        children.push(m_nodes[0]);

        size_t last_index = -1;
        while(!children.empty()) {
            if (children.top().left > -1) {
                Node& n = children.top();
                children.push(m_nodes[n.left]);
                n.left = -1;
                continue;
            }

            Node n = children.top();
            children.pop();

            if (last_index != -1) {
                const Node& last_node = m_nodes[last_index];

                if(last_node.key > n.key)
                    return false;

                if (last_node.key == n.key) {
                    if (last_node.right == -1)
                        return false;

                    if (!hasKey(n.key, m_nodes[last_node.right]))
                        return false;
                }
            }

            last_index = n.index;

            if (n.right > -1)
                children.push(m_nodes[n.right]);
        }

        return true;
    }

    void clear() {
        m_nodes.clear();
    }

    bool hasKey(long int key, const Node& root) const {
        std::queue<const Node*> children;
        children.push(&root);

        while (!children.empty()) {
            const Node* n = children.front();

            if (n->key == key)
                return true;

            if (n->left > -1)
                children.push(&m_nodes[n->left]);

            if (n->right > -1)
                children.push(&m_nodes[n->right]);

            children.pop();
        }

        return false;
    }

 private:
    std::vector<Node> m_nodes;
};

#ifdef DEBUG
void test_solution() {
    Timer timer;

    Tree tree;
    tree.addNode(2, 1, 2);
    tree.addNode(1, -1, -1);
    tree.addNode(3, -1, -1);

    ASSERT_TRUE(tree.isBst());
    EXPECT_LE(timer.elapsed(), 1000);

    timer.restart();

    tree.clear();
    tree.addNode(1, 1, 2);
    tree.addNode(2, -1, -1);
    tree.addNode(3, -1, -1);

    ASSERT_FALSE(tree.isBst());
    EXPECT_LE(timer.elapsed(), 1000);

    timer.restart();

    tree.clear();
    ASSERT_TRUE(tree.isBst());
    EXPECT_LE(timer.elapsed(), 1000);

    timer.restart();

    tree.clear();
    tree.addNode(1, -1, 1);
    tree.addNode(2, -1, 2);
    tree.addNode(3, -1, 3);
    tree.addNode(4, -1, 4);
    tree.addNode(5, -1, -1);

    ASSERT_TRUE(tree.isBst());
    EXPECT_LE(timer.elapsed(), 1000);

    timer.restart();

    tree.clear();
    tree.addNode(4, 1, 2);
    tree.addNode(2, 3, 4);
    tree.addNode(6, 5, 6);
    tree.addNode(1, -1, -1);
    tree.addNode(3, -1, -1);
    tree.addNode(5, -1, -1);
    tree.addNode(7, -1, -1);

    ASSERT_TRUE(tree.isBst());
    EXPECT_LE(timer.elapsed(), 1000);

    timer.restart();

    tree.clear();
    tree.addNode(4, 1, -1);
    tree.addNode(2, 2, 3);
    tree.addNode(1, -1, -1);
    tree.addNode(5, -1, -1);

    ASSERT_FALSE(tree.isBst());
    EXPECT_LE(timer.elapsed(), 1000);

    timer.restart();

    tree.clear();
    tree.addNode(2, 1, 2);
    tree.addNode(1, -1, -1);
    tree.addNode(2, -1, -1);

    ASSERT_TRUE(tree.isBst());
    EXPECT_LE(timer.elapsed(), 1000);

    timer.restart();

    tree.clear();
    tree.addNode(2, 1, 2);
    tree.addNode(2, -1, -1);
    tree.addNode(3, -1, -1);

    ASSERT_FALSE(tree.isBst());
    EXPECT_LE(timer.elapsed(), 1000);

    timer.restart();

    tree.clear();
    tree.addNode(2147483647, -1, -1);

    ASSERT_TRUE(tree.isBst());
    EXPECT_LE(timer.elapsed(), 1000);
}
#endif
}  // namespace

int main(int argc, char** argv) {
    if (argc == 1) {
        size_t vertices;
        std::cin >> vertices;

        Tree tree;
        for (size_t i = 0; i < vertices; ++i) {
            long int key;
            std::cin >> key;

            int left;
            std::cin >> left;

            int right;
            std::cin >> right;

            tree.addNode(key, left, right);
        }

        if (tree.isBst())
            std::cout << "CORRECT" << std::endl;
        else
            std::cout << "INCORRECT" << std::endl;

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
