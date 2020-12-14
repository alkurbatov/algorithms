#include <algorithm>
#include <iostream>
#include <limits>
#include <vector>

#ifdef DEBUG
#include <gtest/gtest.h>

#include "utils/timer.h"
#endif

namespace
{
struct Node;

struct Link
{
    Link(const Node* to_, int cost_): to(to_), cost(cost_)
    {}

    const Node* to;
    int cost;
};

struct Node
{
    explicit Node(unsigned id_): id(id_)
    {}

    unsigned id = 0;
    std::vector<Link> links;
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

    void link(unsigned from_, unsigned to_, int cost_)
    {
        m_nodes[from_ - 1].links.emplace_back(&m_nodes[to_ - 1], cost_);
    }

    bool hasNegativeCycle() const
    {
        std::vector<int> dist(m_nodes.size(), std::numeric_limits<int>::max());

        for (size_t it = 0; it < m_nodes.size() - 1; ++it)
        {
            for (size_t i = 0; i < m_nodes.size(); ++i)
            {
                if (dist[i] == std::numeric_limits<int>::max())
                    dist[i] = 0;

                for (const auto& link : m_nodes[i].links)
                {
                    int nextMoveCost = dist[i] + link.cost;
                    if (dist[link.to->id - 1] > nextMoveCost)
                        dist[link.to->id - 1] = nextMoveCost;
                }
            }
        }

        for (size_t i = 0; i < m_nodes.size(); ++i)
        {
            for (const auto& link : m_nodes[i].links)
            {
                int nextMoveCost = dist[i] + link.cost;
                if (dist[link.to->id - 1] > nextMoveCost)
                    return true;
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
    graph.link(1, 2, -5);
    graph.link(4, 1, 2);
    graph.link(2, 3, 2);
    graph.link(3, 1, 1);

    ASSERT_TRUE(graph.hasNegativeCycle());
    EXPECT_LE(timer.elapsed(), 2000);

    timer.restart();
    graph.reset(4);

    graph.link(1, 2, 1);
    graph.link(4, 1, 2);
    graph.link(2, 3, 2);
    graph.link(3, 1, -5);

    ASSERT_TRUE(graph.hasNegativeCycle());
    EXPECT_LE(timer.elapsed(), 2000);
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
        int cost;
        for (size_t i = 0; i < m; ++i)
        {
          std::cin >> from >> to >> cost;
          graph.link(from, to, cost);
        }

        std::cout << graph.hasNegativeCycle() << std::endl;

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
