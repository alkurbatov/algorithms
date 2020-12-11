#include <algorithm>
#include <iostream>
#include <limits>
#include <queue>
#include <vector>

#ifdef DEBUG
#include <gtest/gtest.h>

#include "utils/timer.h"
#endif

namespace
{
struct Node;

const int NOT_FOUND = -1;

struct Link
{
    Link(const Node* to_, unsigned cost_): to(to_), cost(cost_)
    {}

    const Node* to;
    unsigned cost;
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

    void link(unsigned from_, unsigned to_, unsigned cost_)
    {
        m_nodes[from_ - 1].links.emplace_back(&m_nodes[to_ - 1], cost_);
    }

    int distance(unsigned from_, unsigned to_) const
    {
        std::vector<unsigned> dist(m_nodes.size(), std::numeric_limits<unsigned>::max());

        auto comparer = [&dist](const auto& lhs_, const auto& rhs_)
        {
            return dist[lhs_->id - 1] > dist[rhs_->id - 1];
        };

        std::priority_queue<const Node*, std::vector<const Node*>, decltype(comparer)> open(comparer);

        open.push(&m_nodes[from_ - 1]);
        dist[from_ - 1] = 0;

        while (!open.empty())
        {
            const Node* node = open.top();
            open.pop();

            if (node->id == to_)
                return dist[node->id - 1];

            for (const auto& link : node->links)
            {
                unsigned nextMoveCost = dist[node->id - 1] + link.cost;
                if (dist[link.to->id - 1] > nextMoveCost)
                {
                    dist[link.to->id - 1] = nextMoveCost;
                    open.push(link.to);
                }
            }
        }

        return NOT_FOUND;
    }

 private:
    std::vector<Node> m_nodes;
};

#ifdef DEBUG
void test_solution() {
    Timer timer;

    Graph graph(4);
    graph.link(1, 2, 1);
    graph.link(4, 1, 2);
    graph.link(2, 3, 2);
    graph.link(1, 3, 5);

    ASSERT_EQ(graph.distance(1, 3), 3);
    EXPECT_LE(timer.elapsed(), 2000);

    timer.restart();
    graph.reset(5);
    graph.link(1, 2, 4);
    graph.link(1, 3, 2);
    graph.link(2, 3, 2);
    graph.link(3, 2, 1);
    graph.link(2, 4, 2);
    graph.link(3, 5, 4);
    graph.link(5, 4, 1);
    graph.link(2, 5, 3);
    graph.link(3, 4, 4);

    ASSERT_EQ(graph.distance(1, 5), 6);
    EXPECT_LE(timer.elapsed(), 2000);

    timer.restart();
    graph.reset(3);
    graph.link(1, 2, 7);
    graph.link(1, 3, 5);
    graph.link(2, 3, 2);

    ASSERT_EQ(graph.distance(3, 2), NOT_FOUND);
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

        unsigned from, to, cost;
        for (size_t i = 0; i < m; ++i)
        {
          std::cin >> from >> to >> cost;
          graph.link(from, to, cost);
        }

        std::cin >> from >> to;
        std::cout << graph.distance(from, to) << std::endl;

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
