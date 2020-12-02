#include <iostream>
#include <stack>
#include <vector>

#ifdef DEBUG
#include <gtest/gtest.h>

#include "utils/timer.h"
#endif

namespace
{
struct Node
{
    explicit Node(unsigned id_): id(id_)
    {}

    unsigned id = 0;
    std::vector<Node*> links;
};

struct Graph
{
    explicit Graph(size_t vertices_)
    {
        reset(vertices_);
    }

    void reset(size_t vertices_)
    {
        m_nodes.clear();

        for (size_t i = 0; i < vertices_; ++i)
            m_nodes.emplace_back(i + 1);
    }

    void link(unsigned from_, unsigned to_)
    {
        m_nodes[from_ - 1].links.push_back(&m_nodes[to_ - 1]);
        m_nodes[to_ - 1].links.push_back(&m_nodes[from_ - 1]);
    }

    bool reachable(unsigned from_, unsigned to_) const
    {
        std::stack<const Node*> open;
        open.push(&m_nodes[from_ - 1]);

        std::vector<unsigned> closed(m_nodes.size(), 0);

        while(!open.empty())
        {
            const Node* node = open.top();
            open.pop();

            if (node->id == to_)
                return true;

            if (closed[node->id - 1])
                continue;

            closed[node->id - 1] = 1;
            for (const auto i : node->links)
                open.push(i);
        }

        return false;
    }

 private:
    std::vector<Node> m_nodes;
};

#ifdef DEBUG
void test_solution() {
    Timer timer;

    Graph graph(4);
    graph.link(1, 2);
    graph.link(3, 2);
    graph.link(4, 3);
    graph.link(1, 4);

    ASSERT_TRUE(graph.reachable(1, 4));
    EXPECT_LE(timer.elapsed(), 1000);

    graph.reset(4);
    graph.link(1, 2);
    graph.link(3, 2);

    ASSERT_FALSE(graph.reachable(1, 4));
    EXPECT_LE(timer.elapsed(), 1000);

    graph.reset(100);
    graph.link(17, 69);
    graph.link(29, 50);
    graph.link(62, 64);
    graph.link(44, 59);
    graph.link(69, 90);
    graph.link(34, 35);
    graph.link(80, 81);
    graph.link(12, 59);
    graph.link(9 ,87);
    graph.link(3 ,51);
    graph.link(49, 68);
    graph.link(85, 90);
    graph.link(24, 39);
    graph.link(48, 10);
    graph.link(74, 83);
    graph.link(14, 24);
    graph.link(64, 82);
    graph.link(54, 90);
    graph.link(60, 86);
    graph.link(32, 71);
    graph.link(57, 76);
    graph.link(6 ,67);
    graph.link(33, 79);
    graph.link(80, 91);
    graph.link(27, 10);
    graph.link(33, 56);
    graph.link(17, 55);
    graph.link(12, 55);
    graph.link(28, 71);
    graph.link(27, 33);
    graph.link(40, 42);
    graph.link(52, 74);
    graph.link(17, 99);
    graph.link(38, 87);
    graph.link(10, 58);
    graph.link(32, 94);
    graph.link(41, 56);
    graph.link(59, 91);
    graph.link(70, 97);
    graph.link(22, 46);
    graph.link(21, 30);
    graph.link(30, 62);
    graph.link(43, 79);
    graph.link(10, 32);
    graph.link(25, 48);
    graph.link(75, 81);
    graph.link(53, 61);
    graph.link(59, 70);
    graph.link(25, 79);
    graph.link(8 ,58);
    graph.link(43, 74);
    graph.link(17, 38);
    graph.link(20, 43);
    graph.link(4 ,80);
    graph.link(77, 81);
    graph.link(37, 64);
    graph.link(34, 43);
    graph.link(58, 73);
    graph.link(43, 50);
    graph.link(44, 53);
    graph.link(81, 83);
    graph.link(29, 42);
    graph.link(14, 97);
    graph.link(19, 57);
    graph.link(79, 93);
    graph.link(59, 90);
    graph.link(64, 77);
    graph.link(22, 80);
    graph.link(18, 73);
    graph.link(44, 99);
    graph.link(31, 75);
    graph.link(18, 59);
    graph.link(23, 55);
    graph.link(42, 91);
    graph.link(39, 63);
    graph.link(30, 37);
    graph.link(30, 56);
    graph.link(9 ,58);
    graph.link(45, 79);
    graph.link(26, 41);
    graph.link(32, 63);
    graph.link(86, 92);
    graph.link(33, 97);
    graph.link(2 ,93);
    graph.link(24, 72);
    graph.link(32, 96);
    graph.link(16, 59);
    graph.link(28, 65);
    graph.link(59, 67);
    graph.link(3 ,98);
    graph.link(19, 82);
    graph.link(14, 62);
    graph.link(21, 22);
    graph.link(44, 76);
    graph.link(17, 30);
    graph.link(43, 87);
    graph.link(21, 69);
    graph.link(43, 47);
    graph.link(86, 96);
    graph.link(68, 96);

    ASSERT_FALSE(graph.reachable(89, 19));
    EXPECT_LE(timer.elapsed(), 1000);
}
#endif
} // namespace

int main(int argc, char* argv[]) {
    if (argc == 1)
    {
        size_t n, m;
        std::cin >> n >> m;

        Graph graph(n);

        unsigned from, to;
        for (size_t i = 0; i < m; ++i)
        {
          std::cin >> from >> to;
          graph.link(from, to);
        }

        std::cin >> from >> to;
        std::cout << graph.reachable(from, to) << std::endl;

        return 0;
    }

#ifdef DEBUG
    if (std::string(argv[1]) == "test")
    {
        test_solution();
        return 0;
    }
#endif

    return 1;
}
