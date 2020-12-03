#include <algorithm>
#include <iostream>
#include <stack>
#include <vector>

#ifdef DEBUG
#include <gmock/gmock.h>
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

    std::vector<unsigned> toposort() const
    {
        std::vector<unsigned> sorted;
        std::vector<unsigned> closed(m_nodes.size(), 0);

        for (size_t i = 0; i < m_nodes.size(); ++i)
        {
            if (closed[i])
                continue;

            std::stack<const Node*> open;
            open.push(&m_nodes[i]);

            while(!open.empty())
            {
                const Node* node = open.top();

                bool expanded = false;
                for (const auto i : node->links)
                {
                    if (closed[i->id - 1])
                        continue;

                    expanded = true;
                    open.push(i);
                }

                if (!expanded)
                {
                    open.pop();

                    if (closed[node->id - 1])
                        continue;

                    closed[node->id - 1] = 1;
                    sorted.push_back(node->id);
                }
            }
        }

        std::reverse(std::begin(sorted), std::end(sorted));
        return sorted;
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
    graph.link(3, 1);

    ASSERT_THAT(graph.toposort(), testing::ElementsAre(4, 3, 1, 2));
    EXPECT_LE(timer.elapsed(), 1000);

    timer.restart();
    graph.reset(4);
    graph.link(3, 1);

    ASSERT_THAT(graph.toposort(), testing::ElementsAre(4, 3, 2, 1));
    EXPECT_LE(timer.elapsed(), 1000);

    timer.restart();
    graph.reset(5);
    graph.link(2, 1);
    graph.link(3, 2);
    graph.link(3, 1);
    graph.link(4, 3);
    graph.link(4, 1);
    graph.link(5, 2);
    graph.link(5, 3);

    ASSERT_THAT(graph.toposort(), testing::ElementsAre(5, 4, 3, 2, 1));
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

        for (const auto i : graph.toposort())
            std::cout << i << " ";
        std::cout << std::endl;

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
