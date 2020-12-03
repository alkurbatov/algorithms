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
    }

    bool hasCycle() const
    {
        std::vector<unsigned> closed(m_nodes.size(), 0);

        for (size_t i = 0; i < m_nodes.size(); ++i)
        {
            if (closed[i])
                continue;

            std::stack<const Node*> open;
            open.push(&m_nodes[i]);

            unsigned start = m_nodes[i].id;
            while(!open.empty())
            {
                const Node* node = open.top();
                open.pop();

                if (closed[node->id - 1])
                {
                    if (node->id == start)
                        return true;

                    continue;
                }

                closed[node->id - 1] = 1;
                for (const auto i : node->links)
                    open.push(i);
            }
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
    graph.link(4, 1);
    graph.link(2, 3);
    graph.link(3, 1);

    ASSERT_TRUE(graph.hasCycle());
    EXPECT_LE(timer.elapsed(), 1000);

    timer.restart();
    graph.reset(5);
    graph.link(1, 2);
    graph.link(2, 3);
    graph.link(1, 3);
    graph.link(3, 4);
    graph.link(1, 4);
    graph.link(2, 5);
    graph.link(3, 5);

    ASSERT_FALSE(graph.hasCycle());
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

        std::cout << graph.hasCycle() << std::endl;

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
